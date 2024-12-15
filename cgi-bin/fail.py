#!/usr/bin/env python3
import time
import sys

def main():
    print('fail active...')

if __name__ == "__main__":
    main()
    print("Content-Type: text/html\r\n\r\n", flush=True)
    sys.exit(53)
