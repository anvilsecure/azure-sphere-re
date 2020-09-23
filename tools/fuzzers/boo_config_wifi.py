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

def emit_json(d):
    def emit_kv(key, value):
        s_delim('"')
        s_string(key)
        s_delim('"')
        s_delim(":")
        s_delim(" ")
        if isinstance(value, str):
            s_delim('"')
            s_string(value)
            s_delim('"')
        else:
            s_int(value, output_format="ascii")
    
    s_string("{")
    s_delim(" ")
    first = True
    for key, value in d.items():
        if not first:
            s_delim(",")
            s_delim(" ")
        emit_kv(key, value)
        first = False
    s_delim(" ")
    s_string("}")

def emit_json_post_request(name, json, fuzzable=True):
    s_initialize(name=name)
    with s_block("Request-Line"):
        s_string("POST", fuzzable = False)
        s_delim(" ", name='space-1', fuzzable = False)
        s_string("/wifi/config/networks", name='uri', fuzzable = False)
        s_delim(" ", name='space-2', fuzzable = False)
        s_string("HTTP/1.1", name='HTTP-Version', fuzzable = False)
    s_delim("\r\n", name='return-1', fuzzable = False)
    s_string("Host:", name="Host", fuzzable = False)
    s_delim(" ", name="space-4", fuzzable = False)
    s_string("192.168.35.2", name="Host-Value", fuzzable = False)
    s_delim("\r\n", name="return-3", fuzzable = False)

    s_string("Content-Type:", name="content-type-hdr", fuzzable=fuzzable)
    s_delim(" ", name="space-5", fuzzable=fuzzable),
    s_string("application/json; charset=utf-8", name="content-type-value", fuzzable=fuzzable)
    s_delim("\r\n", name="return-4", fuzzable = False)

    s_string("Content-Length:", name="content-length-hdr", fuzzable=fuzzable)
    s_delim(" ", name="space-6", fuzzable=fuzzable),
    s_size("body", output_format="ascii", name="content-length", fuzzable=fuzzable)
    s_delim("\r\n", name="return-5", fuzzable = False)

    s_static("\r\n", name="header end crlf")

    with s_block("body"):
        emit_json(json)


emit_json_post_request("PSK-Request", {
        "configState": "enabled",
        "id": -1,
        "psk": "BBBBBBBBBB",
        "securityState": "psk",
        "ssid": "ABCD"
    }
)

emit_json_post_request("EAP-TLS-Request", {
        "clientCertStoreIdentifier": "AAAA",
        "clientIdentity": "BBBB",
        "configName": "ZZZZ",
        "configState": "enabled",
        "id": -1,
        "rootCaCertStoreIdentifier": "CCCCC",
        "securityState": "eaptls",
        "ssid": "ABCDEF"
    }, fuzzable=False
)


session.connect(s_get("PSK-Request"))
session.connect(s_get("EAP-TLS-Request"))

session.fuzz()
