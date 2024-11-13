#!/usr/bin/env python3

import html
import os
import sys
import select
from urllib.parse import parse_qs

HTML_TEMPLATE = """Content-Type: text/html

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
    {content}
    <a href="/">Back to top</a>
</body>
</html>
"""

ERROR_TEMPLATE = """Content-Type: text/html

<html><body><h1>Error: {message}</h1></body></html>"""

def render_html(content):
    return HTML_TEMPLATE.format(content=content)

def render_error(message):
    return ERROR_TEMPLATE.format(message=message)

def get_form_data():
    method = os.environ.get("request_method", "").upper()
    print(f"Method: {method}", file=sys.stderr)

    if method == "POST":
        try:
            length = int(os.environ.get("content_length", 0))
            body = sys.stdin.read(length)
            print(f"Length: {length}, Body: {body}", file=sys.stderr)
            return parse_qs(body), method
        except Exception as e:
            raise RuntimeError(f"Failed to read POST data: {e}")
    elif method == "GET":
        return parse_qs(os.environ.get("query_string", "")), method
    else:
        raise RuntimeError(f"Unsupported method: {method}")

def process_form():
    try:
        parsed, method = get_form_data()
        name = parsed.get("name", [""])[0]
        message = parsed.get("message", [""])[0]
        
        if not (name and message):
            content = "<p>error: incorrect data</p>"
        else:
            content = f"""
            <p>this reply is created followed by {html.escape(method)} request.</p>
            <p>name is: {html.escape(name)}</p>
            <p>message is: {html.escape(message)}</p>
            """
        print(render_html(content))

    except Exception as e:
        print(render_error(str(e)))
        sys.exit(1)

if __name__ == "__main__":
    process_form()
    sys.exit(0)
