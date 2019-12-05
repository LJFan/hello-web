import json
import random
import time
from ctypes import CDLL

import pyodbc
from flask import Flask, request

renju_kernel = CDLL("renju.so")

PORT = '9999'
DEBUG = False

MAX_ROW = 1000

server = 'localhost'
database = 'School'
username = 'user'
password = '1234'

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello World! ' + \
           time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time()))


@app.route('/chinese')
def chinese():
    return '这是一个中文网页'


@app.route('/english')
def english():
    return 'This is an English web'


@app.route('/par')
def par():
    r = request.args.get('info', 'None')
    print(r)
    return 'request info: ' + r


@app.route('/register', methods=['POST'])
def register():
    print(request.headers)
    name = request.form.get('name', default='None')
    password = request.form.get('password', default='None')
    print(name)
    print(password)
    return 'Welcome ' + name + '!'


@app.route('/<anything>/')
def give(anything):
    return anything


@app.route('/shutdown')
def shutdown():
    func = request.environ.get('werkzeug.server.shutdown')
    func()
    return 'Server shutting down...'


"""
@app.route('/sql')
def sql():
    query = request.args.get('query', '')
    if not query:
        return 'Query is empty.'
    print(query)
    cursor.execute(query)

    ret = [query, 'rowcount: ' + str(cursor.rowcount)]
    try:
        for i in range(MAX_ROW):
            r = cursor.fetchone()
            if r is None:
                break
            ret.append(str(r))
        else:
            ret.append('Only show first' + str(MAX_ROW) + ' lines...')
    except pyodbc.ProgrammingError:
        ret.append('No result')

    return '\n'.join(['<p>' + r + '</p>' for r in ret])
"""


@app.route('/renju')
def renju():
    board = request.args.get('board')
    time_start = time.time()
    put = renju_kernel.solve(board.encode('ascii'))
    print('put =', put, ", time =", time.time() - time_start)
    time.sleep(0.01)
    return request.args.get('callback', 'None') + "(" + json.dumps(put) + ")"


if __name__ == '__main__':
    """
    print('Connecting to SQL Server')
    cnxn = pyodbc.connect(
        'DRIVER={ODBC Driver 17 for SQL Server};'
        'SERVER=' + server + ';' +
        'DATABASE=' + database + ';' +
        'UID=' + username + ';' +
        'PWD=' + password)
    cursor = cnxn.cursor()
    """
    print('Web Server is running...')
    app.run(host='0.0.0.0', port=PORT, debug=DEBUG)
