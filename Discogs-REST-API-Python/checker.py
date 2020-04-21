import requests
import json
import time
import sys
from threading import Lock, Thread

def get_request(member_id):
    r = requests.get("https://api.discogs.com/artists/" + str(member_id))

    j = r.json()

    if "groups" in j:
        for group in j["groups"]:
            name = group["name"]

            lock.acquire()
            if name not in bands_dict:
                bands_dict[name] = set()

            bands_dict[name].add(names_dict[member_id])

            lock.release()

r = requests.get('https://api.discogs.com/artists/' + sys.argv[1])
j = r.json()

names_dict = {}
bands_dict = {}

for member in j['members']:
    names_dict[member["id"]] = member["name"]

get_lock = Lock()
lock = Lock()

for member_id in names_dict.keys():
    Thread(target=get_request(member_id)).start()
    time.sleep(2)

print("==========")
for band, artists in bands_dict.items():
    if len(artists) > 1:
        print(band + ": ")
        for artist in artists:
            print(artist)
        print("==========")
