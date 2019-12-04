import requests

url = "https://ezatqspasg.execute-api.ap-southeast-1.amazonaws.com/default/reverseproxy?board="
arg = "000000081808000000000010000000002"
url = "http://ljfan.xyz:9999/renju?board="
arg = "B0000000000000000000000000000000000000000000000000000000000001000000000000000000000000000000000000000000000000000000000000"

r = requests.get(url + arg)
print(r.text)
