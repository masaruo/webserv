#!/usr/bin/env python3
import time
import sys

def main():
    print('sleeping...', file=sys.stderr)
    time.sleep(5)
    print('good morning', file=sys.stderr)

if __name__ == "__main__":
    main()
    print("Content-Type: text/html\r\n\r\n", flush=True)
    sys.exit(0)
