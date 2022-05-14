from bottle import Bottle, run, static_file, route, request
from glob import glob
import os
import json

app = Bottle()

@app.route("/assets/<path>")
def serve_utils(path):
	return static_file(path, root="./static/assets")

@app.route("/game_sprites/<name>")
def serve_game_sprites(name):
	return static_file(name, root="./static/assets/game_sprites")

@app.route("/save", method="POST")
def save_map_file():
	name = request.forms.get("name")
	data = request.forms.get("data")
	output_path = os.path.join("../maps", name)
	if os.path.exists(output_path):
		return "Map already exists"
	with open(output_path, "w") as f:
		f.write(data)
	return "Map saved to {}".format(output_path)

@app.route("/levels")
def levels():
	paths = glob("../maps/*.ber")
	levels = [os.path.basename(path) for path in paths]
	return json.dumps(levels)

@app.route("/load_level", method="POST")
def load():
	name = request.forms.get("name")
	if "~" in name or "." in name or ".ber" not in name:
		return
	path = os.path.join("../maps", name)
	with open(path, "r") as f:
		data = f.read()
	return data

@app.route("/")
def index():
	return static_file("ui.html", root="./static")

run(app, host="localhost", port=12834)
