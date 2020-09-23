#!/usr/bin/env python3

import requests

def upload_data(target, data, timeout=None):
    # first upload the data
    r = requests.put(f"https://{target}/update/stage", data=data, verify=False, timeout=timeout)
    print(r.content)

    # then trigger the install
    r = requests.post(f"https://{target}/update/install", json={"appControlMode":"Auto"}, verify=False, timeout=timeout)
    print(r.content)


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument("image", type=argparse.FileType("rb"))
    parser.add_argument("--target", default="192.168.35.2")
    args = parser.parse_args()

    upload_data(args.target, args.image.read())
