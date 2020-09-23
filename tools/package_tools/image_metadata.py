#!/usr/bin/env python3
import struct
import uuid

import hexdump

import packer

SIGNATURE_LENGTH = 0x40
METADATA_MAGIC = 0x4D345834

class ImageError(Exception):
    pass

class Image:

    def __init__(self, data):
        self.signature = data[-SIGNATURE_LENGTH:]

        meta_length = struct.unpack("<I", data[-(SIGNATURE_LENGTH + 4):-SIGNATURE_LENGTH])[0]
        metadata = data[-(SIGNATURE_LENGTH + meta_length):-SIGNATURE_LENGTH]
        self.body = data[:-(SIGNATURE_LENGTH + meta_length)]

        stream = packer.Unpacker(metadata)

        self.metadata = []
        magic = stream.unpack("<I")[0]
        if magic != METADATA_MAGIC:
            raise ImageError("Invalid magic: {:08x}".format(magic))
        count = stream.unpack("<I")[0]
        for i in range(count):
            id, size = stream.unpack("<HH")
            data = stream.read(size)
            self.metadata.append((id, data))
    
    def render_metadata(self):
        stream = packer.Packer()
        stream.pack("<I", METADATA_MAGIC)
        stream.pack("<I", len(self.metadata))
        for id, data in self.metadata:
            stream.pack("<HH", id, len(data))
            stream.write(data)
        return bytes(stream)

        


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("image", type=argparse.FileType("rb"))
    args = parser.parse_args()

    image = Image(args.image.read())

    print("Metadata:")
    for id, data in image.metadata:
        print("\t{:c}{:c} (0x{:04x}):".format((id & 0xff), (id >> 8), id), hexdump.dump(data))
        if id == 0x4244:
            print("\t\t", str(data[8:], "ascii"))
        elif id == 0x4449:
            print("\t\tComponent ID:", uuid.UUID(bytes_le=data[4:4+16]))
            print("\t\t    Image ID:", uuid.UUID(bytes_le=data[4+16:]))


    print("Signature:")
    hexdump.hexdump(image.signature)





