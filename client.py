import requests

user_info = {'name': 'LJFan', 'password': '123'}
r = requests.post("http://localhost:9999/register", data=user_info)

print(r.text)
