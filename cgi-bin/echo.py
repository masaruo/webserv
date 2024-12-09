#!/usr/bin/env python3

import html
import os
import sys
from urllib.parse import parse_qs

def debug_print():
    print("=== Debug Info ===", file=sys.stderr)
    print("Environment variables:", file=sys.stderr)
    for key, value in os.environ.items():
        print(f"{key}: {value}", file=sys.stderr)
    print("=== End Debug ===\n", file=sys.stderr)

def get_form_data():
    method = os.environ.get("request_method", "").upper()
    # print(f"Method: {method}", file=sys.stderr)

    if method == "POST":
        try:
            length = int(os.environ.get("content_length", 0))
            body = sys.stdin.read(length)
            # print(f"Length: {length}, Body: {body}", file=sys.stderr)
            return parse_qs(body), method
        except Exception as e:
            raise RuntimeError(f"Failed to read POST data: {e}")
    elif method == "GET":
        return parse_qs(os.environ.get("query_string", "")), method
    else:
        raise RuntimeError(f"Unsupported method: {method}")

def process_form():
    print("Content-Type: text/html\r\n\r\n", flush=True)
    try:
        # debug_print()#
        parsed, method = get_form_data()
        name = parsed.get("name", [""])[0]
        message = parsed.get("message", [""])[0]
        
        if not (name and message):
            print("<p>error: incorrect data</p>")
        else:
            print(f"""
            <p>this reply is created followed by {html.escape(method)} request.</p>
            <p>name is: {html.escape(name)}</p>
            <p>message is: {html.escape(message)}</p>
            """)

    except Exception as e:
        print(f"<html><body><h1>Error: {str(e)}</h1></body></html>")
        sys.exit(1)

if __name__ == "__main__":
    process_form()
    sys.exit(0)
