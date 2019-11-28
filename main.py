from flask import Flask, request
import time
import flask

PORT = '9999'
DEBUG = False

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


@app.route('/shutdown')
def shutdown():
    func = request.environ.get('werkzeug.server.shutdown')
    func()
    return 'Trying to shutdown!'



if __name__ == '__main__':
    print('Web Server is running...')
    if DEBUG:
        app.run(port='9999', debug=True)
    else:
        app.run(host='0.0.0.0', port=PORT)
