#!usr/bin/env python
import json
import numpy as np
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--json_file", type=str, required=True, help="json original file path")
args = parser.parse_args()

def data_load():
    records = [json.loads(line) for line in open(args.json_file)]
    return records

records = data_load()
    
for i in records:
    for key in i:
        print(key)
