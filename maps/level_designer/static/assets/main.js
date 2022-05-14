function Lint() {
	let data = ConvertLevel();
	let errors_ul = $("#errors");
	let spawns = (data.match(/P/g) || []).length;
	let exits = (data.match(/E/g) || []).length;
	let collectibles = (data.match(/C/g) || []).length;
	let first_line = data.split("\n")[0];
	let last_line = data.split("\n")[data.split("\n").length - 1];
	errors_ul.empty();
	if (data.match(/[^01PEC\n]/g)) {
		errors_ul.append("<li class='error'>Found an invalid character</li>");
	}
	if (spawns <= 0) {
		errors_ul.append("<li class='error'> No spawn points found.</li>");
	}
	if (exits <= 0) {
		errors_ul.append("<li class='error'> No exit points found.</li>");
	}
	if (collectibles <= 0) {
		errors_ul.append("<li class='error'> No collectible found.</li>");
	}
	if ((first_line.match(/1/g) || []).length != first_line.length) {
		errors_ul.append("<li class='error'>First row of map must be wall only</li>");
	}
	if ((last_line.match(/1/g) || []).length != last_line.length) {
		errors_ul.append("<li class='error'>Last row of map must be wall only</li>");
	}
	// Check if every line starts and ends with a wall
	for (let i = 1; i < data.split("\n").length - 1; i++) {
		let line = data.split("\n")[i];
		if (!(line.startsWith('1') && line.endsWith('1'))) {
			errors_ul.append("<li class='error'>Line " + i + " must start and end with a wall</li>");
		}
	}
	if (spawns > 1) {
		errors_ul.append("<li class='warning'> More than one spawn point found. A random one will be chosen</li>");
	}
	$("#lint > h3").text("Live linter (" + errors_ul.find(".error").length + " errors)");
	if (errors_ul.find(".error").length == 0) {
		errors_ul.append("<li style='color: green;'>Level is valid.</li>");
	}
}

function CreateLevel(width, height) {
	// Create base level template
	let level = $("#level");
	level.empty();
	for (let y = 0; y < height; y++) {
		level.append("<div class='level-row'></div>");
		let row = level.children().last();
		for (let x = 0; x < width; x++) {
			if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
			{
				row.append("<div class='level-tile bleak_desk_clock_112x112'></div>");
			}
			else
			{
				row.append("<div class='level-tile background_1_112x112'></div>");
			}
		}
	}
	// Listen for clicks on tiles
	$(".level-tile").click(function() {
		let selected_class = $(".selected").attr("src").split('/').pop().replace(".png", "");
		// Remove classes from clicked tile
		$(this).removeClass().addClass("level-tile");
		// Add class to clicked tile
		$(this).addClass(selected_class);
		Lint();
	});
}

function Load(data) {
	for (let index = 0; index < data.length; index++) {
		$("#level .level-tile").eq(index).removeClass().addClass("level-tile " + CharToClass(data[index]));
	}
	Lint();
}

function GenerateTemplate() {
	var levelSize = prompt("Enter the size of the level (e.g. 6x6):", "6x6");
	if (levelSize == null) {
		return;
	}
	let height, width;
	[width, height] = levelSize.split("x");
	if (height == null || width == null) {
		alert("Invalid level size");
		return;
	}
	CreateLevel(parseInt(width), parseInt(height));
	// Listen for clicks on img	
	$("img").click(function() {
		$(".selected").removeClass("selected");
		$(this).addClass("selected");
	});

	// Listen for CTRL+S
	$(document).keydown(function(e) {
		if (e.ctrlKey && e.keyCode == 83) {
			e.preventDefault();
			SaveLevel();
		}
	});
}

function CharToClass(name) {
	switch (name) {
		case "0":
			return "ice";
		case "1":
			return "wall";
		case "P":
			return "player";
		case "E":
			return "berry";
		case "C":
			return "seed";
		default:
			return "unknown";
	}
}

function ClassToChar(name) {
	switch (name) {
		case "background_1_112x112":
			return "0";
		case "bleak_desk_clock_112x112":
			return "1";
		case "moonkey_112x112":
			return "P";
		case "exit_112x112":
			return "E";
		case "form_1_112x112":
			return "C";
		default:
			return "?";
	}
}

function saveAs(data, name) {
	console.log("Saving level as " + name);
	$.post("/save", {"data":data, "name":name}, function(data) {
		alert(data);
	});
}

function saveAsLocal(data, name) {
	console.log("Saving level as " + name);
	let blob = new Blob([data], {type: "text/plain;charset=utf-8"});
	let url = URL.createObjectURL(blob);
	let a = document.createElement("a");
	a.href = url;
	a.download = name;
	a.click();
	URL.revokeObjectURL(url);
}

function ConvertLevel() {
	let output = "";
	let rows = $(".level-row");
	for (let i = 0; i < rows.length; i++) {
		let tiles = $(rows[i]).find(".level-tile");
		for (let j = 0; j < tiles.length; j++) {
			output += ClassToChar($(tiles[j]).attr("class").split(" ")[1]);
		}
		output += "\n";
	}
	// Strip last newline
	output = output.substring(0, output.length - 1);
	return output
}

function SaveLevel() {
	let name = prompt("Enter the name of the level:", "level.ber");
	if (!name.endsWith(".ber"))
	{
		name += ".ber";
	}
	if ($("#save-remote").is(":checked")) {
		saveAs(ConvertLevel(), name);
	}
	if ($("#save-locally").is(":checked")) {
		saveAsLocal(ConvertLevel(), name);
	}
}

function GetLevels() {
	$("#level-select").empty();
	$.get("/levels", function (data) {
		let levels = JSON.parse(data);
		let level_select = $("#level-select");
		for (let i = 0; i < levels.length; i++) {
			level_select.append("<option value='" + levels[i] + "'>" + levels[i] + "</option>");
		}
	});
	// Listen for changes
	$("#level-select").change(function() {
		let name = $(this).val();
		$.post("/load_level", {"name":name}, function(data) {
			let lines = data.split("\n");
			let width, height;
			height = lines.length;
			width = lines[0].length;
			CreateLevel(width, height);
			Load(data.replaceAll("\n", ""));
		});
	});
}

$(document).ready(function() {
	GenerateTemplate();
	GetLevels();
	Lint();
});
