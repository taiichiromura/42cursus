#include "Cgi.hpp"
#include "Client.hpp"
#include "ScopedFd.hpp"
#include "Utils.hpp"
#include "unistd.h"
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/wait.h>

std::string CGI::do_cgi(std::string cgi_path, std::string filepath,
                        std::string query, Client* client) {
  int pipe_fd[2];
  if (pipe(pipe_fd) < 0)
    return "";
  ScopedFd readEnd(pipe_fd[0]);
  ScopedFd writeEnd(pipe_fd[1]);

  int pid = fork();
  if (pid < 0)
    return "";

  if (pid == 0) {
    dup2(writeEnd.get(), STDOUT_FILENO);
    readEnd.reset();
    writeEnd.reset();

    char* argv[] = {(char*)cgi_path.c_str(), (char*)filepath.c_str(), NULL};
    std::string method = "REQUEST_METHOD=GET";
    std::string qs = "QUERY_STRING=" + query;
    std::string path_info = "PATH_INFO=" + client->getRequestTarget();
    std::string protocol = "SERVER_PROTOCOL=HTTP/1.1";
    std::string script_name = "SCRIPT_NAME=" + client->getRequestTarget();

    char* envp[] = {(char*)method.c_str(),      (char*)qs.c_str(),
                    (char*)path_info.c_str(),   (char*)protocol.c_str(),
                    (char*)script_name.c_str(), NULL};
    execve(argv[0], argv, envp);
    exit(1);
  }

  writeEnd.reset();

  int flags = fcntl(readEnd.get(), F_GETFL, 0);
  fcntl(readEnd.get(), F_SETFL, flags | O_NONBLOCK);

  client->setCgiPid(pid);
  client->setCgiOutFd(readEnd.release());
  client->setIsCgiRunning(true);
  client->setCgiStartTime(time(NULL));
  client->setCgiLastActivity(time(NULL));
  return "";
}

std::string CGI::do_cgi_post(std::string cgi_path, std::string filepath,
                             std::string body, Client* client) {
  int in_fds[2];
  int out_fds[2];

  if (pipe(in_fds) < 0)
    return "";
  ScopedFd inRead(in_fds[0]);
  ScopedFd inWrite(in_fds[1]);

  if (pipe(out_fds) < 0)
    return "";
  ScopedFd outRead(out_fds[0]);
  ScopedFd outWrite(out_fds[1]);

  int pid = fork();
  if (pid < 0)
    return "";

  if (pid == 0) {
    dup2(inRead.get(), STDIN_FILENO);
    dup2(outWrite.get(), STDOUT_FILENO);
    inRead.reset();
    outWrite.reset();
    inWrite.reset();
    outRead.reset();
    char* argv[] = {(char*)cgi_path.c_str(), (char*)filepath.c_str(), NULL};
    std::string size_str = ft_to_string(body.size());
    std::string method = "REQUEST_METHOD=POST";
    std::string len = "CONTENT_LENGTH=" + size_str;
    std::string path_info = "PATH_INFO=" + client->getRequestTarget();
    std::string protocol = "SERVER_PROTOCOL=HTTP/1.1";
    std::string secret = "HTTP_X_SECRET_HEADER_FOR_TEST=1";
    char* envp[] = {(char*)method.c_str(),    (char*)len.c_str(),
                    (char*)path_info.c_str(), (char*)protocol.c_str(),
                    (char*)secret.c_str(),    NULL};
    execve(argv[0], argv, envp);
    exit(1);
  }

  // 親プロセス側: 子に渡した側は不要
  inRead.reset();
  outWrite.reset();

  int outFlags = fcntl(outRead.get(), F_GETFL, 0);
  fcntl(outRead.get(), F_SETFL, outFlags | O_NONBLOCK);
  int inFlags = fcntl(inWrite.get(), F_GETFL, 0);
  fcntl(inWrite.get(), F_SETFL, inFlags | O_NONBLOCK);

  client->setCgiPid(pid);
  client->setCgiInFd(
      inWrite.release()); // 所有権をClientへ譲渡、以後closeしない
  client->setCgiOutFd(outRead.release());
  client->setIsCgiRunning(true);
  client->setBodyBytesWritten(0);
  client->setCgiStartTime(time(NULL));
  client->setCgiLastActivity(time(NULL));
  return "";
}
