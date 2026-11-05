#include "Client.hpp"
#include "Utils.hpp"

#include <iostream>
#include <sstream>

static const char* const kMethodsUse[] = {"GET", "DELETE", "POST"};
static const char* const kMethodsNotUse[] = {"HEAD",  "OPTIONS", "TRACE",
                                             "PATCH", "CONNECT", "PUT"};

const std::vector<std::string> Client::methodsUse(kMethodsUse, kMethodsUse + 3);
const std::vector<std::string> Client::methodsNotUse(kMethodsNotUse,
                                                     kMethodsNotUse + 6);

Client::Client()
    : _cgiStartTime(0), _cgiLastActivity(0), _isSending(false), _server(NULL),
      _phase(PARSE_HEADER), _statusCode(200), _sentRequest(false),
      _isParseCompleted(false), _isChunked(false), _cgiPid(-1), _cgiOutFd(-1),
      _isCgiRunning(false), _expectedChunkSize(0), _chunkState(CHUNK_SIZE),
      _isCookie(false), _cgiInFd(-1), _bodyBytesWritten(0), _cgiOutput(""),
      _request(""), _lastRequest(time(NULL)), _requestTarget(""), _method(""),
      _resource(""), _httpVersion(""), _body(""), _recv(""), _contentLength(0),
      _server_port(0), _sessionId(""), _response_bytes_sent(0), _closeAfterSend(false) {}

Client::~Client() {}

void Client::setRequest(const char* buf, const int& len) {
  this->_request.append(buf, len);
}

const std::string& Client::getFields(const std::string& key) const {
  std::map<std::string, std::string, CaseInsensitiveLess>::const_iterator it =
      this->_fields.find(key);
  if (it == this->_fields.end()) {
    static const std::string empty_string = "";
    return empty_string;
  }
  return it->second;
}

int Client::validateMethod() const {
  for (int i = 0; i < 3; i++) {
    if (this->_method == methodsUse[i])
      return 200;
  }
  for (int i = 0; i < 6; i++) {
    if (this->_method == methodsNotUse[i])
      return 405;
  }
  return 400;
}

int Client::validateRequestTarget() const {
  if (this->_requestTarget.size() > 8192)
    return 414;
  if (this->_requestTarget[0] != '/')
    return 400;
  if (this->hasDotDotSegment())
    return 400;
  int i = 0;
  while (this->_requestTarget[i]) {
    if (this->_requestTarget == " ")
      return 400;
    i++;
  }
  return 0;
}

int Client::validateHttpVersion() const {
  if (this->_httpVersion != "HTTP/1.1")
    return 505;
  return 0;
}

int Client::parseHeader(std::string& request) {
  size_t first_line_end = request.find("\r\n");
  if (first_line_end == std::string::npos)
    return 1;

  std::string first_line = request.substr(0, first_line_end);
  size_t first_space = first_line.find(' ');
  if (first_space == std::string::npos)
    return 1;

  size_t second_space = first_line.find(' ', first_space + 1);
  if (second_space == std::string::npos)
    return 1;

  this->_method = first_line.substr(0, first_space);
  this->_requestTarget =
      first_line.substr(first_space + 1, second_space - (first_space + 1));
  this->_requestTarget = urlDecode(this->_requestTarget);
  this->_httpVersion = first_line.substr(second_space + 1);

  this->parseFields(request, first_line_end + 2);

  int methodStatus = this->validateMethod();
  if (methodStatus != 200)
    this->_statusCode = methodStatus;

  int targetStatus = this->validateRequestTarget();
  if (targetStatus != 0)
    this->_statusCode = targetStatus;

  int versionStatus = this->validateHttpVersion();
  if (versionStatus != 0)
    this->_statusCode = versionStatus;

  this->setPhase(PARSE_BODY);
  return 0;
}

size_t Client::ftHexaToDecimal(std::string rawChunke, bool& ok) {
  ok = true;
  if (rawChunke.empty()) {
    ok = false;
    return 0;
  }
  size_t decimalValue = 0;
  for (size_t i = 0; i < rawChunke.size(); i++) {
    char c = rawChunke[i];
    size_t digit;
    if (c >= '0' && c <= '9') digit = c - '0';
    else if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
    else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
    else {
      ok = false;
      return 0;
    }
    decimalValue = decimalValue * 16 + digit;
  }
  return decimalValue;
}

void Client::processChunkedRequest(std::string& chunkedRequest) {
  while (true) {
    if (this->_chunkState == CHUNK_SIZE) {
      size_t chunkeSize = chunkedRequest.find("\r\n");
      if (chunkeSize == std::string::npos)
        return;
      std::string rawChunk = chunkedRequest.substr(0, chunkeSize);

      bool ok = true;
      this->_expectedChunkSize = ftHexaToDecimal(rawChunk, ok);
      if (!ok) {
        this->_statusCode = 400;
        this->_phase = COMPLETE;
        return;
      }
      if (this->_expectedChunkSize == 0) {
        this->_chunkState = CHUNK_END;
        this->_phase = COMPLETE;
        return;
      }
      chunkedRequest = chunkedRequest.substr(chunkeSize + 2);
      this->_chunkState = CHUNK_DATA;
    }
    if (this->_chunkState == CHUNK_DATA) {
      if (chunkedRequest.size() < this->_expectedChunkSize + 2)
        return;
      this->_body += chunkedRequest.substr(0, this->_expectedChunkSize);
      chunkedRequest = chunkedRequest.substr(this->_expectedChunkSize + 2);
      this->_chunkState = CHUNK_SIZE;
    }
    if (this->_chunkState == CHUNK_END) {
      this->_phase = COMPLETE;
      return;
    }
  }
}

void Client::processNormalBody(const std::string& request) {
  if (request.size() >= _contentLength) {
    _body = request.substr(0, _contentLength);
    _phase = COMPLETE;
  } else {
    _body = request;
  }
}
void Client::parseFields(std::string& request, size_t i) {
  size_t header_end = this->consumeHeaderLines(request, i);
  if (header_end == std::string::npos)
    return;

  this->stripHeaderFromRequest(request, header_end);
  this->validateHostHeader();
  this->parseCookieHeader();
  this->determineBodyTransferMode();
  this->detectConnectionClose();
}

// ヘッダー行を1行ずつ_fieldsに積む。
// 空行(ヘッダー終端)の開始位置を返す。途中でデータが尽きていればnposを返す。
size_t Client::consumeHeaderLines(std::string& request, size_t i) {
  while (i < request.size()) {
    size_t lineLen = request.find("\r\n", i);
    if (lineLen == std::string::npos)
      return std::string::npos;
    if (lineLen == i)
      return i;
    std::string line = request.substr(i, lineLen - i);
    this->divideKeyAndValue(line);
    i += line.size() + 2;
  }
  return i;
}

void Client::stripHeaderFromRequest(std::string& request, size_t header_end) {
  size_t body_start = header_end + 2;
  if (body_start <= request.size())
    request = request.substr(body_start);
  else
    request.clear();
}

void Client::validateHostHeader() {
  if (this->_fields.find("Host") == this->_fields.end())
    this->_statusCode = 400;
}

void Client::parseCookieHeader() {
  std::string cookie = this->getFields("Cookie");
  size_t last_valid = cookie.find_last_not_of(" \t\r\n");
  cookie =
      (last_valid != std::string::npos) ? cookie.substr(0, last_valid + 1) : "";

  std::string prefix = "session_id=";
  size_t pos = cookie.find(prefix);
  if (pos == std::string::npos) {
    this->_isCookie = false;
    return;
  }

  std::string id_value = cookie.substr(pos + prefix.length());
  size_t semi_pos = id_value.find(";");
  if (semi_pos != std::string::npos)
    id_value = id_value.substr(0, semi_pos);

  size_t first = id_value.find_first_not_of(" \t");
  size_t last = id_value.find_last_not_of(" \t");
  if (first != std::string::npos && last != std::string::npos)
    id_value = id_value.substr(first, last - first + 1);

  this->_isCookie = !id_value.empty();
  if (this->_isCookie)
    this->_sessionId = id_value;
}

void Client::determineBodyTransferMode() {
  bool hasContentLength = this->_fields.find("Content-Length") != this->_fields.end();
  bool hasTransferEncoding = !this->getFields("Transfer-Encoding").empty();

  if (hasContentLength && hasTransferEncoding) {
    this->_statusCode = 400;
    this->_phase = COMPLETE;
    return;
  }
  if (hasContentLength) {
    this->_contentLength = ft_stoi(this->_fields["Content-Length"]);
  } else if (ft_trim(this->getFields("Transfer-Encoding")) == "chunked") {
    this->_isChunked = true;
  } else {
    this->_phase = COMPLETE;
  }
}

void Client::divideKeyAndValue(std::string line) {
  size_t keyPos = line.find(":");
  if (keyPos == std::string::npos)
    return;
  std::string key = line.substr(0, keyPos);
  std::string value = line.substr(keyPos + 1);

  CaseInsensitiveLess less;
  bool isHostKey = !less(key, "Host") && !less("Host", key);
  if (isHostKey && this->_fields.find("Host") != this->_fields.end())
    this->_statusCode = 400;

  this->_fields[key] = value;
}

void Client::setResponseStr(const std::string& str) {
  this->_res.setResponseStr(str);
  this->_response_bytes_sent = 0;
}

const std::string& Client::getResponseStr() const {
  return this->_res.getResponseStr();
}

void Client::appendCgiOutput(const char* buf, size_t n) {
  // cgi処理でエラーがあったらアペンドしない
  if (this->_cgiOutput.find("500 Internal Server Error") != std::string::npos)
    return;
  this->_cgiOutput.append(buf, n);
}

void Client::clearForNextRequest() {
  this->_isSending = false;
  this->_phase = PARSE_HEADER;
  this->_statusCode = 200;
  this->_sentRequest = false;
  this->_isParseCompleted = false;
  this->_isChunked = false;

  this->_expectedChunkSize = 0;
  this->_chunkState = CHUNK_SIZE;

  this->_cgiPid = -1;
  this->_cgiOutFd = -1;
  this->_cgiInFd = -1;
  this->_isCgiRunning = false;
  this->_bodyBytesWritten = 0;
  this->_cgiOutput.clear();

  this->_request.clear();
  this->_requestTarget.clear();
  this->_method.clear();
  this->_resource.clear();
  this->_httpVersion.clear();
  this->_body.clear();
  this->_recv.clear();
  this->_fields.clear();

  this->_contentLength = 0;
  this->_response_bytes_sent = 0;

  this->_res = Response();

  this->_lastRequest = time(NULL);
  this->_closeAfterSend = false;
}

// ---- サーバー設定 ----
void Client::setServer(ConfigServer& server) {
  this->_server = &server;
}
ConfigServer& Client::getServer() {
  return *(this->_server);
}
void Client::setServerPort(int port) {
  this->_server_port = port;
}

// ---- レスポンス送信 ----
size_t& Client::getResponseBytesSent() {
  return this->_response_bytes_sent;
}

// ---- CGI ----
void Client::setCgiPid(int pid) {
  this->_cgiPid = pid;
}
int Client::getCgiPid() const {
  return this->_cgiPid;
}

void Client::setCgiOutFd(int fd) {
  this->_cgiOutFd = fd;
}
int Client::getCgiOutFd() const {
  return this->_cgiOutFd;
}

void Client::setCgiInFd(int fd) {
  this->_cgiInFd = fd;
}
int Client::getCgiInFd() const {
  return this->_cgiInFd;
}

void Client::setIsCgiRunning(bool tr) {
  this->_isCgiRunning = tr;
}
bool Client::getIsCgiRunning() const {
  return this->_isCgiRunning;
}

std::string& Client::getCgiOutput() {
  return this->_cgiOutput;
}

void Client::setCgiStartTime(time_t t) {
  this->_cgiStartTime = t;
}
void Client::setCgiLastActivity(time_t t) {
  this->_cgiLastActivity = t;
}
time_t Client::getCgiLastActivity() const {
  return this->_cgiLastActivity;
}

void Client::setBodyBytesWritten(size_t bytes) {
  this->_bodyBytesWritten = bytes;
}
void Client::addBodyBytesWritten(size_t bytes) {
  this->_bodyBytesWritten += bytes;
}
size_t Client::getBodyBytesWritten() const {
  return this->_bodyBytesWritten;
}

// ---- タイマー ----
time_t Client::getClientLastRequest() const {
  return this->_lastRequest;
}
void Client::setClientLastRequest(time_t t) {
  this->_lastRequest = t;
}

// ---- その他アクセサ ----
const std::string& Client::getRequest() const {
  return this->_request;
}
std::string& Client::getRefRequest() {
  return this->_request;
}
const std::string& Client::getRequestTarget() const {
  return this->_requestTarget;
}
const std::string& Client::getMethod() const {
  return this->_method;
}
const std::string& Client::getBody() const {
  return this->_body;
}
std::string& Client::getBody() {
  return this->_body;
}
RequestPhase Client::getPhase() const {
  return this->_phase;
}
void Client::setPhase(RequestPhase phase) {
  this->_phase = phase;
}
const int& Client::getStatusCode() const {
  return this->_statusCode;
}
void Client::setStatusCode(int statusCode) {
  this->_statusCode = statusCode;
}
bool Client::getIsChunked() const {
  return this->_isChunked;
}
const bool& Client::getParseCompleted() const {
  return this->_isParseCompleted;
}
const std::map<std::string, std::string, CaseInsensitiveLess>& Client::getFields() const {
  return this->_fields;
}
const std::string Client::getField(std::string key) const {
  return this->_fields.at(key);
}
bool Client::getIsCookie() const {
  return this->_isCookie;
}
const std::string& Client::getSessionId() const {
  return this->_sessionId;
}
const std::map<int, std::string>& Client::getErrorPagesMap() const {
  return this->_error_pages_map;
}

bool Client::hasDotDotSegment() const {
  const std::string& path = this->_requestTarget;
  size_t start = 0;
  while (start <= path.size()) {
    size_t end = path.find('/', start);
    std::string segment = (end == std::string::npos)
                               ? path.substr(start)
                               : path.substr(start, end - start);
    if (segment == "..")
      return true;
    if (end == std::string::npos)
      break;
    start = end + 1;
  }
  return false;
}

void Client::detectConnectionClose() {
  std::string connection = ft_trim(this->getFields("Connection"));
  CaseInsensitiveLess less;
  bool isClose = !less(connection, "close") && !less("close", connection);
  if (isClose)
    this->_closeAfterSend = true;
}

bool Client::getCloseAfterSend() const {
  return this->_closeAfterSend;
}
void Client::setCloseAfterSend(bool value) {
  this->_closeAfterSend = value;
}

int Client::getServerPort() const {
  return this->_server_port;
}
