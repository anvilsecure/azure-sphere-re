#!/usr/bin/env python3

from Cryptodome.PublicKey import ECC
from Cryptodome.Signature import DSS
from Cryptodome.Hash import SHA256

_PRIVATE_KEY = '''-----BEGIN PRIVATE KEY-----
MIGHAgEAMBMGByqGSM49AgEGCCqGSM49AwEHBG0wawIBAQQgSxn0uAPxCKxUsISx
PrTivexGGbxxpq5+An5KDNlZdaahRANCAATt8jPADTEUHY8/VjNDQMzYwWn7Z+Ls
Vkv4pe9Yaxw/e8GIyiCHAebXx3VqEyY4/pjJoCAHQD3lxCLmp+gmpL0k
-----END PRIVATE KEY-----
'''

_PUBLIC_KEY = '''-----BEGIN CERTIFICATE-----
MIICMDCCAdWgAwIBAgIJAKH4XtbTyQ8QMAoGCCqGSM49BAMCMHQxCzAJBgNVBAYT
AlVTMRMwEQYDVQQIDApXYXNoaW5ndG9uMRAwDgYDVQQHDAdSZWRtb25kMR4wHAYD
VQQKDBVNaWNyb3NvZnQgQ29ycG9yYXRpb24xHjAcBgNVBAMMFUF6dXJlIFNwaGVy
ZSBTREsgVGVzdDAeFw0xODA1MjIwMTE2MjVaFw0zODA1MTcwMTE2MjVaMHQxCzAJ
BgNVBAYTAlVTMRMwEQYDVQQIDApXYXNoaW5ndG9uMRAwDgYDVQQHDAdSZWRtb25k
MR4wHAYDVQQKDBVNaWNyb3NvZnQgQ29ycG9yYXRpb24xHjAcBgNVBAMMFUF6dXJl
IFNwaGVyZSBTREsgVGVzdDBZMBMGByqGSM49AgEGCCqGSM49AwEHA0IABO3yM8AN
MRQdjz9WM0NAzNjBaftn4uxWS/il71hrHD97wYjKIIcB5tfHdWoTJjj+mMmgIAdA
PeXEIuan6CakvSSjUDBOMB0GA1UdDgQWBBRjsI/w+PfZeFjjM5tQcFL6HcyeizAf
BgNVHSMEGDAWgBRjsI/w+PfZeFjjM5tQcFL6HcyeizAMBgNVHRMEBTADAQH/MAoG
CCqGSM49BAMCA0kAMEYCIQD2dyGZaKdjz5/90K7OH+d8A5zc7tLvviXa3KEucrGv
ugIhAIoNe5ddI4GhgN4FWOMlnq+VgWzeP25sowIc4g4dFFtC
-----END CERTIFICATE-----
'''

def calculate_signature(data, key_data=_PRIVATE_KEY):
    key = ECC.import_key(key_data)
    signer = DSS.new(key, 'fips-186-3')

    return signer.sign(SHA256.new(data))

def verify_signature(data, signature, key_data=_PUBLIC_KEY):
    key = ECC.import_key(key_data)
    verifier = DSS.new(key, 'fips-186-3')

    verifier.verify(SHA256.new(data), signature)



if __name__ == "__main__":
    import argparse
    import hexdump

    def sign(args):
        data = args.file.read()

        sig = calculate_signature(data)

        print("Calculated Signature:")
        hexdump.hexdump(sig)

        if args.out != None:
            args.out.write(data)
            args.out.write(sig)

    def verify(args):
        data = args.file.read()

        sig = data[-0x40:]
        data = data[:-0x40]

        try:
            verify_signature(data, sig)
            print("Verified!")
        except ValueError:
            print("Signature is invalid!")

    parser = argparse.ArgumentParser()

    subparsers = parser.add_subparsers(dest="cmd", required=True)

    subparser = subparsers.add_parser("sign")
    subparser.add_argument("file", type=argparse.FileType("rb"))
    subparser.add_argument("--out", type=argparse.FileType("wb"))
    subparser.set_defaults(func=sign)

    subparser = subparsers.add_parser("verify")
    subparser.add_argument("file", type=argparse.FileType("rb"))
    subparser.set_defaults(func=verify)

    args = parser.parse_args()
    args.func(args)
