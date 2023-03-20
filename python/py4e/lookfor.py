#!/bin/python3

filename = input("enter a file name: ")
confidences = []

if filename == 'na na boo boo':
    print("are you ok ?")

with open(filename, 'r') as f:
    for line in f:
        if line.startswith("X-DSPAM-Confidence:"):
            extracted_confidence = line.split(':')[1].strip()
            confidences.append(float(extracted_confidence))
    print(sum(confidences) / len(confidences))

