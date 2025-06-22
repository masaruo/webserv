#!/usr/bin/env python3
import time
import sys
import os

def sleep():
    print('sleeping...', file=sys.stderr)
    time.sleep(30)
    print('good morning', file=sys.stderr)

def chunked():
    print('chunk start...', file=sys.stderr)
    #! 小文字の環境変数名を使用
    length = int(os.environ.get("content_length", "0"))
    # print(f'Content length: {length}', file=sys.stderr)  # length確認用
    body = sys.stdin.read(length)
    print(f'Received body: {body}', file=sys.stderr)
    print('chunk end...', file=sys.stderr)

def print_env():
    print("=== Debug Info ===", file=sys.stderr)
    print("Environment variables:", file=sys.stderr)
    for key, value in os.environ.items():
        print(f"{key}: {value}", file=sys.stderr)
    print("=== End Debug ===\n", file=sys.stderr)

if __name__ == "__main__":
    # sleep()
    print_env()
    chunked()
    print("Content-Type: text/html\r\n\r\n", flush=True)
    sys.exit(0)
