#!/usr/bin/env python3
import argparse
import ssl

from boofuzz import *
import requests

import package_tools.image_metadata as im
from package_tools import uploader, signer

import monitors

parser = argparse.ArgumentParser()
parser.add_argument("template_file", type=argparse.FileType("rb"))
parser.add_argument("--target", default="192.168.35.2")
parser.add_argument("--gui", action="store_true", default=0)
parser.add_argument("--start", type=int, default=1)
args = parser.parse_args()

image = im.Image(args.template_file.read())

class Uploader(ITargetConnection):

    def __init__(self, target, timeout=None):
        self.target = target
        self.timeout = timeout
    
    @property
    def info(self):
        return self.target
    
    def close(self):
        pass

    def open(self):
        pass

    def recv(self, max_bytes):
        return b""
    
    def send(self, data):
        data_len = len(data)
        data += signer.calculate_signature(data)
        uploader.upload_data(self.target, data, timeout=self.timeout)
        #open("/mnt/hgfs/tmp/foo.bin", "wb").write(data)
        #print("Hit enter", len(data))
        #input()
        return data_len


session = Session(
    console_gui=args.gui,
    index_start=args.start,
    target = Target(
        connection=Uploader(args.target),
        monitors=[monitors.GatewayMonitor(args.target)]
    )
)

# create our boofuz package

s_initialize("image")
s_static(image.body)

with s_block("metadata"):
    s_dword(im.METADATA_MAGIC, fuzzable=False, name='magic')
    s_dword(len(image.metadata), name='count') # I don't know how to make a "count" in boofuzz

    for i, (id, data) in enumerate(image.metadata):
        name = "meta_{:04x}".format(id)
        s_short(id, name="tag_{:04x}".format(id))
        s_size(name, length=2, name="length_{:04x}".format(id))
        with s_block(name):
            s_bytes(data, name="value_{:04x}".format(id))
s_size("metadata", inclusive=True, name="metadata_size")

session.connect(s_get("image"))
session.fuzz()
