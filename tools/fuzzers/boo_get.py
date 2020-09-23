#!/usr/bin/env python3

import ssl    
import argparse

# Designed for use with boofuzz v0.0.9
from boofuzz import *

import monitors

parser = argparse.ArgumentParser()
parser.add_argument("--target", default="192.168.35.2")
parser.add_argument("--gui", action="store_true", default=0)
parser.add_argument("--start", type=int, default=1)
args = parser.parse_args()


ctx = ssl.create_default_context()
ctx.check_hostname = False
ctx.verify_mode = ssl.CERT_NONE

session = Session(
    console_gui=args.gui,
    index_start=args.start,
    target=Target(
        connection=SSLSocketConnection(args.target, 443, sslcontext=ctx),
        monitors=[monitors.GatewayMonitor(args.target)]
    ),
)

get_urls = [
    "/abi_versions",
    "/restart",
    "/status",
    "/log",
    "/images",
    "/telemetry",
    "/wifi/scan",
    "/wifi/config/networks",
    "/wifi/diagnostics/networks",
    "/update/stage",
    "/update/install",
    "/app/status",
    "/app/image",
    "/app/quota",
    "/net/interfaces",
    "/net/status",
    "/device/manufacturing_state",
    "/device/security_state",
    "/certstore/certs",
    "/certstore/space",
]

s_initialize(name="Request")
with s_block("Request-Line"):
    s_group("Method", ["GET"])
    s_delim(" ", name='space-1')
    s_group('Request-URI', get_urls)
    s_delim(" ", name='space-2')
    s_string("HTTP/1.1", name='HTTP-Version')
s_delim("\r\n", name='return-1', fuzzable = False)
s_string("AZSPHERE-CAPABILITIES:", name="AZSPHERE-CAPABILITIES")
s_delim(" ", name="space-3")
s_string("/Vz9XAEAAADMAAAAe+5YCy62OR0nKrQr9i/dzE4Kq3R1wLGv+w1c4k8qrLoeQkIk1rVxAFUYrv2JqQDZoz6y6HlVmM9jgm40jLzaogsAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAANFg0TQMAAABJRCQADQAAANi1KEHCq1VBmjOKHzHtZ+xw5S7lJaxaS6eNIEt6bVy6U0cYAEioDtltJhjWCD5aZgTZY7JY5IauAQAAAERCKADOwQ9fAAAAAGZ3X2NvbmZpZwAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAfAAAADpWJ0OwDZrdM67hHoncxAOs44dIsl3lDpwiqoWzAa5EuneG69XNIH8CwGZT+BMQUWZaCRlJtHOQB1Jk9WubxTA=                                        ", name="AZSPHERE-CAPABILITIES-Value")
s_delim("\r\n", name="return-2", fuzzable = False)
s_string("Host:", name="Host")
s_delim(" ", name="space-4")
s_string("192.168.35.2", name="Host-Value")
s_delim("\r\n", name="return-3", fuzzable = False)
s_static("\r\n", name="Request-Line-CRLF")
s_static("\r\n", "Request-CRLF")

session.connect(s_get("Request"))

session.fuzz()
