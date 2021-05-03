'''
@Author: George Zhao
@Date: 2020-03-20 15:54:19
LastEditors: George Zhao
LastEditTime: 2021-05-03 13:54:18
@Description:
@Email: 2018221138@email.szu.edu.cn
@Company: SZU
@Version: 1.0
'''
from flask import abort, jsonify, Flask, request, Response
from flask import make_response, send_from_directory
import datetime
from flask_cors import CORS
import hashlib
import os
import sys
import time
import base64

import argparse

Port = 8080
path_to_exe = ""

if os.path.exists("./out/") == False:
    os.mkdir("./out/")
if os.path.exists("./out/img/") == False:
    os.mkdir("./out/img/")
if os.path.exists("./tmp/") == False:
    os.mkdir("./tmp/")

app = Flask(__name__)
CORS(app, resources=r'/*')

libpath = os.path.join(os.path.abspath('.'), 'lib')


@app.route("/")
def index_page():
    return send_from_directory(libpath, 'index.html', as_attachment=False)


@app.route("/<path:filename>")
def index_page_file(filename):
    if filename == 'favicon.ico':
        filename = 'assets/' + filename
    return send_from_directory(libpath, filename, as_attachment=False)


@app.route('/LineAndArrow')
def LindAndArrow():
    try:
        data = base64.b64decode(request.args['Data']).decode("utf-8")
        if not data:
            return data
        t = hashlib.sha256((data + str(time.time() * 1000000)).encode('utf-8'))
        filename = t.hexdigest()
        with open("./tmp/{}.data".format(filename), "w+") as f:
            f.write(data)
        os.system(
            f"{path_to_exe} --datapath ./ --tmppath ./ -i ./tmp/{filename}.data -o ./out/img/{filename} -w {request.args['width']}")
        svgdata = str()
        pngdata = str()
        if os.path.exists("./out/img/{}.svg".format(filename)) == False:
            return "Sorry, Error. May Check Your Input."
        with open("./out/img/{}.svg".format(filename)) as f:
            svgdata = f.read()
        with open("./out/img/{}.png".format(filename), 'rb') as f:
            pngdata = f.read()

        with open("./out/img/{}.pdf".format(filename), 'rb') as f:
            pdfdata = f.read()

        os.remove("./out/img/{}.svg".format(filename))
        os.remove("./out/img/{}.pdf".format(filename))
        os.remove("./out/img/{}.png".format(filename))
        os.remove("./tmp/{}.data".format(filename))
        if request.args['D'] == '1':
            resp = make_response(svgdata)
            resp.headers["Content-Disposition"] = "attachment; filename={}.svg".format(
                filename)
            return resp
        if request.args['D'] == '2':
            resp = make_response(pdfdata)
            resp.headers["Content-Disposition"] = "attachment; filename={}.pdf".format(
                filename)
            return resp
        else:
            return "<img src=\"data:image/png;base64,{}\" style=\"width: 100%; height: 100%;\"/>".format(base64.b64encode(pngdata).decode('utf-8'))
    except BaseException as e:
        print(e)
        return "Sorry, Error. May Check Your Input.\nError Code: \n" + str(e)


def cors_response(res):
    response = make_response(jsonify(res))
    response.headers['Access-Control-Allow-Origin'] = '*'
    response.headers['Access-Control-Allow-Methods'] = 'PUT,GET,POST,DELETE,OPTIONS'
    response.headers['Access-Control-Allow-Headers'] = 'Content-Type, X-Requested-With'
    return response


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-e', type=str, help='Path to LineAndArrow.')
    parser.add_argument('--port', type=int, help='Port', default=Port)
    args = parser.parse_args()
    path_to_exe = args.e
    Port = args.port
    app.config['JSON_AS_ASCII'] = False
    app.run(host='0.0.0.0', port=Port, debug=False)
