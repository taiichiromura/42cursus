#!/bin/bash

# POST body は stdin に来る
read BODY

echo "Content-Type: text/plain"
echo ""

echo "POST CGI OK"
echo "BODY = $BODY"
