#!/bin/bash
echo "Content-Type: text/html"
echo ""
echo "<html><body><h1>Hello CGI</h1><p>Method: $REQUEST_METHOD</p></body></html>"
