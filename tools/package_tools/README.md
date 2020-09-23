# Azure Sphere Package Tools

These are some tools to work with the images in the recovery firmware and application images. The tools can be run alone, or imported into other scripts.

## Dependencies

The scripts need the following packages:

```
> pip3 install hexdump
> pip3 install requests
> pip3 install pycryptodomex
```

## Image Metadata Parser

A simple script to parse and create the metadata fields at the end of each image file.

```
> ./image_metadata.py main.imagepackage 
Metadata:
	ID (0x4449): 0A 00 00 00 57 5C AE 61 CD 98 0A 4A 8B 60 95 09 50 5C 76 17 39 8D 9C F7 AB 21 F9 44 80 2D 25 F4 78 EE A1 BA
		Component ID: 61ae5c57-98cd-4a0a-8b60-9509505c7617
		    Image ID: f79c8d39-21ab-44f9-802d-25f478eea1ba
	SG (0x4753): A8 D5 CC 69 58 F4 87 10 14 0D 7A 26 16 0F C1 CF C3 1F 5D F0 01 00 00 00
	DB (0x4244): 7C 95 6B 5F 00 00 00 00 41 7A 75 72 65 42 75 73 79 62 6F 78 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
		 AzureBusybox
	TP (0x5054): 02 00 00 00
	ND (0x444e): 01 00 00 00 05 00 00 00 03 00 00 00
Signature:
00000000: 21 6C BC FB 9F 14 5D 08  01 33 D0 33 E1 4B 46 C2  !l....]..3.3.KF.
00000010: EA 8A 94 87 21 C4 A2 77  28 D7 B0 CF 96 FA 3B 46  ....!..w(.....;F
00000020: 06 C4 A4 C6 85 6D 1C 90  2B 59 52 33 49 D7 60 C4  .....m..+YR3I.`.
00000030: 25 CE BB DE 33 D6 64 B3  07 7B CA E2 BD C1 93 3C  %...3.d..{.....<

```

## Signer

Python script that signs an image file using the development key embedded within the azpshere CLI tool.

Verify a file:

```
> ./signer.py verify main.imagepackage
Verified!
```

Generate a signature for a file:

```
> ./signer.py sign main.imagepackage 
Calculated Signature:
00000000: AD 62 53 A7 11 E3 4E 8D  5E 49 0F 50 DE 92 7C F5  .bS...N.^I.P..|.
00000010: BA 9B F5 5D 4E E6 1E A2  93 9D 7D CF 23 B9 93 D4  ...]N.....}.#...
00000020: D5 65 BF 6A CC 04 66 43  D7 73 8D 9A D7 09 2B 3E  .e.j..fC.s....+>
00000030: 21 F2 62 77 0D 72 81 A6  61 17 19 8E 98 CD E5 10  !.bw.r..a.......
```

Append a signature to a file:

```
> ./signer.py sign main.imagepackage --out main_signed.imagepackage
Calculated Signature:
00000000: 25 AE 80 51 67 C2 46 17  FB CB B7 0C 68 C2 20 B5  %..Qg.F.....h. .
00000010: 24 1E 05 DF E9 D2 9A 19  49 44 C2 FC AD 26 E5 02  $.......ID...&..
00000020: 17 57 C2 E4 66 4B 9A AA  A1 FA B9 03 8F 3D EC 0F  .W..fK.......=..
00000030: 14 E3 68 55 A0 BE 4C 64  B3 27 56 9E EA 07 AF 3B  ..hU..Ld.'V....;
```

## Uploader

A python script to side load apps onto a device. Does the same functionality as the `azphere dev sl deploy -p <app_image_path>`, but without any client side checks.

```
> ./uploader.py main.imagepackage
/usr/lib/python3/dist-packages/urllib3/connectionpool.py:999: InsecureRequestWarning: Unverified HTTPS request is being made to host '192.168.35.2'. Adding certificate verification is strongly advised. See: https://urllib3.readthedocs.io/en/latest/advanced-usage.html#ssl-warnings
  warnings.warn(
b'{}'
/usr/lib/python3/dist-packages/urllib3/connectionpool.py:999: InsecureRequestWarning: Unverified HTTPS request is being made to host '192.168.35.2'. Adding certificate verification is strongly advised. See: https://urllib3.readthedocs.io/en/latest/advanced-usage.html#ssl-warnings
  warnings.warn(
b'{"error":0}'
```



