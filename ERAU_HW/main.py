""""
Code that may help w/ final project
"""
import json

with open("temp.json") as file:
    s = file.read()
records = json.loads(s)  # list of dicts

def info(d: dict) -> float:
    return d["pressure"]
print(min(records, key=info))  # prints dict with the lowest pressure

# ---------------------------------------------------------------------------------------------------------------------
"""def function but simpler"""
print(max(records, key=lambda d: d["temp"]))  # prints dict with the highest temp

# ---------------------------------------------------------------------------------------------------------------------
lst = [r["temp"] for r in records]
print(max(lst))  # prints just the highest temp

# ---------------------------------------------------------------------------------------------------------------------
max_temp = records[0]  # only use this if all entries have "temp" otherwise records[0].get("temp")
for record in records:  # record is a dictionary
    if record["temp"] > max_temp["temp"]:
        max_temp = record
print(max_temp)  # prints dictionary with the highest temp
