from flask import Flask

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


if __name__ == '__main__':
    print('Web Server is running...')
    app.run(port='9999')
