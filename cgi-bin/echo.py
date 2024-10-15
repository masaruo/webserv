#!/usr/bin/env python3

import html
import os
import sys
import select
from urllib.parse import parse_qs

def print_header():
    print("""Content-Type: text/html

    <!DOCTYPE html>
    <html lang="en">
    <head>
        <meta charset="UTF-8">
        <title>Form Process Outcome</title>
        <link rel="icon" href="data:,">
        <style>
            body { font-family: Arial, sans-serif; line-height: 1.6; padding: 20px; }
            h1 { color: #333; }
        </style>
    </head>
    <body>
        <h1>Form Process Result</h1>
    """)

def print_footer():
    print("""
    <a href="/">Back to top</a>
    </body>
    </html>
    """)

def read_with_timeout(timeout=2):  # タイムアウトを5秒から2秒に変更
    try:
        rlist, _, _ = select.select([sys.stdin], [], [], timeout)
        if rlist:
            return sys.stdin.read()
        else:
            print("Content-Type: text/html\n")
            print("<html><body><h1>Error: Input timeout</h1></body></html>")
            sys.exit(1)
    except Exception as e:
        print("Content-Type: text/html\n")
        print(f"<html><body><h1>Error: {str(e)}</h1></body></html>")
        sys.exit(1)

def process_form():
    method = os.environ.get("request_method", "").upper()
    print(f"Method: {method}", file=sys.stderr)

    if method == "POST":
        try:
            length = int(os.environ.get("content_length", 0))
            print(f"Expected length: {length}", file=sys.stderr)
            body = sys.stdin.read(length)  # この行を変更
            print(f"Actual length: {len(body)}", file=sys.stderr)
            parsed = parse_qs(body)
        except Exception as e:  # この例外処理を追加
            print(f"Error reading input: {e}", file=sys.stderr)
            print_header()
            print(f"<p>Error: {str(e)}</p>")
            print_footer()
            sys.exit(1)
    elif method == "GET":
        query = os.environ.get("query_string", "")
        parsed = parse_qs(query)
    else:
        print(f"Unsupported method: {method}", file=sys.stderr)
        print_header()
        print("<p>Error: Unsupported HTTP method</p>")
        print_footer()
        sys.exit(1)

    name = parsed.get("name", [""])[0]
    message = parsed.get("message", [""])[0]

    print_header()

    print(f">>>cwd is: {os.getcwd()}<<<", file=sys.stderr)

    if name and message:
        print(f"<p>this reply is created followed by {html.escape(method)} request. </p>")
        print(f"<p>name is: {html.escape(name)}</p>")
        print(f"<p>message is: {html.escape(message)}</p>")
    else:
        print("<p>error: incorrect data</p>")
    
    print_footer()

if __name__ == "__main__":
    process_form()
    sys.exit(0)
