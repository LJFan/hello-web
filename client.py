import requests
from ctypes import CDLL
renju_kernel = CDLL("renju.so")


url = "https://ezatqspasg.execute-api.ap-southeast-1.amazonaws.com/default/reverseproxy?board="
arg = "000000081808000000000010000000002"
url = "http://ljfan.xyz:9999/renju?board="
arg = "B2000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000"

r = renju_kernel.solve(arg.encode('ascii'))
print(r)
"""
r = requests.get(url + arg)
print(r.text)
"""