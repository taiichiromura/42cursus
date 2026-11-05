#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ConfigServer.hpp"
#include "Response.hpp"
#include "Utils.hpp"
#include <string>
enum RequestPhase {
  PARSE_HEADER, // ヘッダーを読んでいるステージ
  PARSE_BODY,   // ボディを読んでいるステージ
  COMPLETE      // 全部読み終わったステージ
};

enum ChunkState {
  CHUNK_SIZE, // 16進数のサイズを読み取っている最中
  CHUNK_DATA, // 実際のボディデータを読み取っている最中
  CHUNK_END // すべてのチャンクを読み終えた（0\r\n\r\nが来た）
};

class Client {
private:
  time_t _cgiStartTime;
  time_t _cgiLastActivity;
  bool _isSending;
  static const std::vector<std::string> methodsUse;
  static const std::vector<std::string> methodsNotUse;
  ConfigServer* _server;
  RequestPhase _phase;
  int _statusCode;
  bool _sentRequest;
  bool _isParseCompleted;
  bool _isChunked;
  int _cgiPid;
  int _cgiOutFd;
  bool _isCgiRunning;
  size_t _expectedChunkSize;
  ChunkState _chunkState;
  bool _isCookie;
  int _cgiInFd;
  size_t _bodyBytesWritten;
  std::string _cgiOutput;
  std::string _request;
  time_t _lastRequest;
  std::string _requestTarget;
  std::string _method;
  std::string _resource;
  std::string _httpVersion;
  std::string _body;
  std::string _recv;
  std::map<int, std::string> _error_pages_map;

  std::map<std::string, std::string, CaseInsensitiveLess> _fields;
  size_t _contentLength;
  Response _res;
  int _server_port;
  std::string _sessionId;
  size_t _response_bytes_sent;
  bool _closeAfterSend;

  void divideKeyAndValue(std::string line);
  void parseFields(std::string& request, size_t i);

  size_t consumeHeaderLines(std::string& request, size_t i);
  void stripHeaderFromRequest(std::string& request, size_t header_end);
  void validateHostHeader();
  void parseCookieHeader();
  void determineBodyTransferMode();
  int validateMethod() const;
  int validateRequestTarget() const;
  int validateHttpVersion()const;
  bool hasDotDotSegment() const;
  void detectConnectionClose();

public:
  Client();
  ~Client();

  // ---- リクエスト受信・解析 ----
  void setRequest(const char* buf, const int& len);
  const std::string& getRequest() const;
  std::string& getRefRequest();

  int parseHeader(std::string& request);
  void processChunkedRequest(std::string& chunkedRequest);
  void processNormalBody(const std::string& request);
  size_t ftHexaToDecimal(std::string rawChunke, bool& ok);

  const std::string& getRequestTarget() const;
  const std::string& getMethod() const;

  const std::string& getBody() const;
  std::string& getBody();

  RequestPhase getPhase() const;
  void setPhase(RequestPhase phase);

  const int& getStatusCode() const;
  void setStatusCode(int statusCode);

  bool getIsChunked() const;
  const bool& getParseCompleted() const;

  // ---- ヘッダーフィールド / Cookie ----
  const std::string& getFields(const std::string& key) const;
  const std::map<std::string, std::string, CaseInsensitiveLess>& getFields() const;
  const std::string getField(std::string key) const;

  bool getIsCookie() const;
  const std::string& getSessionId() const;

  const std::map<int, std::string>& getErrorPagesMap() const;

  // ---- サーバー設定 ----
  void setServer(ConfigServer& server);
  ConfigServer& getServer();
  void setServerPort(int port);

  // ---- レスポンス送信 ----
  void setResponseStr(const std::string& str);
  const std::string& getResponseStr() const;
  size_t& getResponseBytesSent();

  // ---- CGI ----
  void setCgiPid(int pid);
  int getCgiPid() const;

  void setCgiOutFd(int fd);
  int getCgiOutFd() const;

  void setCgiInFd(int fd);
  int getCgiInFd() const;

  void setIsCgiRunning(bool tr);
  bool getIsCgiRunning() const;

  void appendCgiOutput(const char* buf, size_t n);
  std::string& getCgiOutput();

  void setCgiStartTime(time_t t);
  void setCgiLastActivity(time_t t);
  time_t getCgiLastActivity() const;

  void setBodyBytesWritten(size_t bytes);
  void addBodyBytesWritten(size_t bytes);
  size_t getBodyBytesWritten() const;

  // ---- タイマー ----
  time_t getClientLastRequest() const;
  void setClientLastRequest(time_t t);

  void clearForNextRequest();

  bool getCloseAfterSend() const;
  void setCloseAfterSend(bool value);

  int getServerPort() const;
};

#endif
