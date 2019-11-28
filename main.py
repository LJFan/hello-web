from flask import Flask, request

app = Flask(__name__)


@app.route('/')
def hello_world():
    return 'Hello World!'


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
    print(request.stream.read())
    return 'welcome'


if __name__ == '__main__':
    print('Web Server is running...')
    # app.run(port='9999')
    app.run(host='0.0.0.0', port='9999')
