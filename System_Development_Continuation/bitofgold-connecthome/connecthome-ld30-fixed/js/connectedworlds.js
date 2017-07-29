// Connect Home
// By László Matuska @BitOfGold
// www.bitofgold.com
// Made for Ludum Dare 30
// In 48 hours
//
// Please Vote! :)

var debugmode = false;
var h = window.innerHeight;
var w = window.innerWidth;
var game = new Phaser.Game(w, h, Phaser.AUTO, '', null,false,false);

var ThisGame = function (game) { };
ThisGame.Boot = function (game) { };
ThisGame.Load = function (game) { };
ThisGame.Menu = function (game) { };
ThisGame.Play = function (game) { };
ThisGame.Win = function (game) { };
ThisGame.End = function (game) { };

var background;
var level;
var gui;
var board = [];
var levelx = 0;
var levely = 0;
var totallevels = 100;
var actuallevel = 0;
var player;
var SCALE = 1.0;
var fontloaded = false;

var levels = [
[
[0,0,0,0,0,0,4,0,0,0,0,0,0],
[0,1,1,1,1,1,3,1,1,1,1,1,0],
[0,1,0,0,0,1,3,1,0,0,0,1,0],
[0,1,0,0,0,1,3,1,0,0,0,1,0],
[0,1,0,9,0,0,0,0,2,0,0,1,0],
[0,1,0,0,0,1,3,1,0,0,0,1,0],
[0,1,0,0,0,1,3,1,0,0,0,1,0],
[0,1,0,2,0,0,0,0,0,0,0,1,0],
[0,1,0,0,0,1,3,1,0,0,0,1,0],
[0,1,0,0,0,1,3,1,0,0,0,1,0],
[0,1,0,0,0,1,3,1,0,0,0,1,0],
[0,1,1,1,1,1,3,1,1,1,1,1,0],
[0,0,0,0,0,0,6,0,0,0,0,0,0]
]
,
[
[0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,1,1,1,1,1,1,1,1,1,1,0],
[0,1,0,0,0,0,0,0,0,0,0,1,0],
[0,1,9,2,0,2,0,2,0,2,0,1,0],
[5,3,0,3,0,3,0,3,0,3,3,3,7],
[0,1,1,1,1,1,1,1,1,1,1,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0]
]
,
[
[0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,1,1,1,1,1,1,1,1,1,1,1,0],
[0,1,0,0,0,0,0,0,0,0,0,0,1,0],
[0,1,0,0,0,2,0,0,0,0,1,1,1,0],
[0,1,1,1,1,1,3,0,3,0,3,3,3,7],
[0,1,0,0,0,0,0,0,0,0,0,0,1,0],
[0,1,0,0,0,0,3,0,0,0,0,0,1,0],
[0,1,0,0,0,0,0,1,1,2,1,1,1,0],
[0,1,0,0,0,0,3,1,0,0,0,0,1,0],
[5,3,3,0,3,3,3,1,0,2,0,0,1,0],
[0,1,0,0,2,0,0,2,0,0,2,0,1,0],
[0,1,0,9,0,0,0,1,0,0,0,0,1,0],
[0,1,1,1,1,1,1,1,1,1,1,1,1,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0]
]
,
[
[0,0,4,0,0,0,0,0,0,0,0,0,0],
[0,1,3,3,1,1,1,1,1,1,1,1,0],
[0,1,0,2,0,0,0,0,0,0,0,1,0],
[0,1,0,0,0,9,0,0,0,0,0,1,0],
[0,1,0,3,3,3,2,2,3,0,0,1,0],
[0,1,0,3,0,0,0,0,3,0,0,1,0],
[0,1,0,2,0,3,3,0,3,0,0,1,0],
[0,1,0,3,0,0,3,0,2,0,0,1,0],
[0,1,0,3,3,3,3,0,2,0,0,1,0],
[0,1,0,0,0,0,0,0,3,0,0,1,0],
[0,1,0,0,0,0,0,0,3,0,0,1,0],
[0,1,1,1,1,1,1,1,3,1,1,1,0],
[0,0,0,0,0,0,0,0,6,0,0,0,0]
]
];

// - Play ------------------------------------------------------------------------------------------

ThisGame.Play.prototype = {

preload: function() {
},

loadlevel: function(num) {
	level.removeAll(true);
	background.removeAll(true);

	var l = levels[num];
	levelx = l[0].length;
	levely = l.length;
	board = JSON.parse( JSON.stringify( l ) );
	
	var tiles = [
		'board',
		'ic',
		'connect',
		'fixconnect',
		'bluev', //4
		'blueh', //5
		'redv',  //6
		'redh',  //7
		'switch',
		'player'
	];
	var obj;
	for (var x = 0; x<levelx; x++) {
		for (var y = 0; y<levely; y ++) {
			var spr = tiles[l[y][x]];
			var xx = x * 34 * SCALE;
			var yy = y * 34 * SCALE;
			obj = game.add.isoSprite(xx, yy, -32 * SCALE, 'board', 0, background);
			obj.anchor.set(0.5,1);
			obj.scale.set(SCALE);
			if (spr == 'player') {
				player = game.add.isoSprite(xx, yy, -40 * SCALE, 'dude', 0, level);
				player.anchor.set(0.5);
				player.scale.set(SCALE);
				player.animations.add('stand-dl',[0],8,true);
				player.animations.add('stand-dr',[3],8,true);
				player.animations.add('stand-ul',[6],8,true);
				player.animations.add('stand-ur',[9],8,true);
				player.animations.add('run-dl',[0,1,0,2],8,true);
				player.animations.add('run-dr',[3,4,3,5],8,true);
				player.animations.add('run-ul',[6,7,6,8],8,true);
				player.animations.add('run-ur',[9,10,9,11],8,true);
				game.physics.isoArcade.enable(player);
				player.body.collideWorldBounds = true;
				player.status = 'stand';
				player.direction = 'dl';
				player.animations.play(player.status+'-'+player.direction);
			} else {
				if (spr != 'board') {
					obj = game.add.isoSprite(xx, yy, -32 * SCALE, spr, 0, level);
					obj.type = spr;
					obj.anchor.set(0.5,1);
					obj.scale.set(SCALE);
					game.physics.isoArcade.enable(obj);
					obj.body.collideWorldBounds = true;
					obj.body.bounce.set(0, 0, 0);
					obj.body.drag.set(500 * SCALE, 500 * SCALE, 0);
					if (spr=='ic' || spr=='fixconnect'
						|| spr=='blueh' || spr=='bluev' || spr=='redh' || spr=='redv') {
						obj.body.moves = false;
						obj.body.immovable = true;
					}
				}
			}
		}
	}
	game.camera.follow(player);
},

gamelogic: function() {
	for (var x = 0; x<levelx; x++) {
		for (var y = 0; y<levely; y ++) {
			board[y][x] = 0;
		}
	}
	pulling = false;
	level.forEachAlive(function(o) {
		var xd = o.isoX / 34 * SCALE;
		var yd = o.isoY / 34 * SCALE;
		var x = Math.round(xd);
		var y = Math.round(yd);
		xd = xd - x;
		yd = yd - y;
		if (o.type=='connect' || o.type=='fixconnect'
			|| o.type=='blueh' || o.type=='bluev' || o.type=='redh' || o.type=='redv') {
			board[y][x] = 1;
		}
		if (o.type=='connect') {
			if (Math.abs(xd)>0.0001 && Math.abs(o.body.velocity.x)<20) {
				o.body.velocity.x += -xd * 200;
			} else {
				pulling = true;
			}
			if (Math.abs(yd)>0.0001 && Math.abs(o.body.velocity.y)<20) {
				o.body.velocity.y += -yd * 200;
			} else {
				pulling = true;
			}
		}
	},this);
		
	this.testwin();
},

//test for winning condition
testwin: function() {
	var win = false;
	
	var fromx = -1;
	var fromy = -1;
	var tox = -1;
	var toy = -1;
	for (var x = 0; x<levelx; x++) {
		if (board[0][x] == 1) {
			fromx = x;
			fromy = 0;
		}
		if (board[levely-1][x] == 1) {
			tox = x;
			toy = levely-1;
		}
	}
	var tr;
	if (fromx != -1 && tox != -1) {
		tr = this.trace(fromx,fromy,tox,toy);
	}
	
	if (!tr) {
		var fromx = -1;
		var fromy = -1;
		var tox = -1;
		var toy = -1;
		for (var y = 0; y<levely; y++) {
			if (board[y][0] == 1) {
				fromx = 0;
				fromy = y;
			}
			if (board[y][levelx-1] == 1) {
				tox = levelx-1;
				toy = y;
			}
		}
		if (fromx != -1 && tox != -1) {
			tr = this.trace(fromx,fromy,tox,toy);
		}
		if (tr) {
			win = true;
		}
	} else {
		win = true;
	}
	if (win) {
		this.dowin();
	}
},

trace: function(fromx,fromy,tox,toy) {
	if (fromx<0 || fromx>=levelx || fromy<0 || fromy>levely) {
		return(false);
	}
	if (board[fromy][fromx] != 1) {
		return(false);
	}
	board[fromy][fromx] = -1;
	if (fromx==tox && fromy == toy) {
		board[fromy][fromx] = -2;
		return(true)
	}
	var found = false
	if (this.trace(fromx+1,fromy,tox,toy)) {found = true;}
	if (this.trace(fromx-1,fromy,tox,toy)) {found = true;}
	if (this.trace(fromx,fromy+1,tox,toy)) {found = true;}
	if (this.trace(fromx,fromy-1,tox,toy)) {found = true;}
	if (found) {
		board[fromy][fromx] = -2;
	}
	return(found);
},

board_dump: function() {
	console.clear();
	for (var y = 0; y<levely; y ++) {
		var s = "";
		for (var x = 0; x<levelx; x++) {
			s += ("   "+board[y][x]).slice(-3)+ ',';
		}
		console.log(("    "+y+".:").slice(-4)+s);
	}
},

dowin: function() {
	if (debugmode) {
		this.board_dump();
		console.log('WIN!');
	}
	if (actuallevel+1>=levels.length) {
		game.state.start('End');
	} else {
		game.state.start('Win');
	}
},

create: function() {
	game.time.advancedTiming = true;
	game.plugins.add(new Phaser.Plugin.Isometric(game));
	game.world.setBounds(0,0,4096,4096);
	game.physics.startSystem(Phaser.Plugin.Isometric.ISOARCADE);
	game.iso.anchor.setTo(0.5,0.5);
	game.physics.isoArcade.gravity.setTo(0, 0, -500 * SCALE);

	//fixed restart button
	this.buttonrestart = game.add.button(w-5, 5, 'buttons', this.restart, this,0,0,0,0);
	this.buttonrestart.anchor.setTo(1,0);
	this.buttonrestart.scale.setTo(0.5);
	this.buttonrestart.fixedToCamera = true;

	this.cursors = game.input.keyboard.createCursorKeys();

	this.game.input.keyboard.addKeyCapture([
		Phaser.Keyboard.LEFT,
		Phaser.Keyboard.RIGHT,
		Phaser.Keyboard.UP,
		Phaser.Keyboard.DOWN,
	]);
	
	var esc = game.input.keyboard.addKey(Phaser.Keyboard.ESC);
	if (debugmode) {
		esc.onDown.add(function () {
			this.dowin();
		}, this);
	}

	background = game.add.group();
	level = game.add.group();
	gui = game.add.group();
	this.loadlevel(actuallevel);
},

restart: function() {
	this.loadlevel(actuallevel);
},

update: function()  {
	game.physics.isoArcade.collide(level);

	var speed = 100 * SCALE;

	if (!player) {return;}
	
	if (this.cursors.up.isDown) {
		player.body.velocity.y = -speed;
	} else if (this.cursors.down.isDown) {
		player.body.velocity.y = speed;
	} else {
		player.body.velocity.y = 0;
	}

	if (this.cursors.left.isDown) {
		player.body.velocity.x = -speed;
	} else if (this.cursors.right.isDown) {
		player.body.velocity.x = speed;
	} else {
		player.body.velocity.x = 0;
	}
	var newstatus = player.status;
	var newdir = player.direction;
	if (player.body.velocity.x==0 && player.body.velocity.y == 0) {
		newstatus = 'stand';
	} else {
		newstatus = 'run';
		var dirx = player.body.velocity.x*0.5 - player.body.velocity.y*0.5;
		var diry = -player.body.velocity.x*0.5 - player.body.velocity.y*0.5;
		if (diry<=0) {
			newdir = 'd';
		} else {
			newdir = 'u';
		}
		if (dirx<0) {
			newdir = newdir+'l';
		} else {
			newdir = newdir+'r';
		}
	}
	
	if (newstatus=='stand') {
		if (player.status != 'stand') {
			player.status = newstatus;
			player.animations.play(player.status+'-'+player.direction);
		}
	} else {
		if (player.status != 'run' || player.direction != newdir ) {
			player.status = newstatus;
			player.direction = newdir;
			player.animations.play(player.status+'-'+player.direction);
		}
	}
	player.status = newstatus;
	player.direction = newdir;

	this.gamelogic();

	game.iso.topologicalSort(level);
},

render: function()  {
	if (debugmode) {
		game.debug.text(game.time.fps || '--', 2, 14, "#aaa");
	}
}

};

// - Menu ------------------------------------------------------------------------------------------

ThisGame.Menu.prototype = {

create: function() {
	this.title = game.add.image(w/2, h*0.2, 'title');
	this.title.anchor.setTo(0.5);

	this.player = game.add.sprite(w/2, h*0.2+32,'dude');
	this.player.anchor.set(0.5,0);
	this.player.animations.add('run-dl',[0,1,0,2],8,true);
	this.player.animations.play('run-dl');

	this.text = game.add.text(game.world.centerX, h*0.5, 
	"Help this Little Dude from another world\nto make a connection home!\n\n"
	+"Push the metal boxes to connect\nthe red and the blue wires!\n\nControls: arrow keys",
	{font:'20px Tahoma', fill: '#8c993a',align:'center'});
	this.text.anchor.setTo(0.5);

	this.buttonstart = game.add.button(w/2, h*0.8, 'bigbuttons', this.startbutton, this,1,0,1,1);
	this.buttonstart.anchor.setTo(0.5);
},

update: function()  {
},

startbutton: function(button) {
	game.state.start('Play');
},

};

// - Win -------------------------------------------------------------------------------------------

ThisGame.Win.prototype = {

create: function() {
	this.player = game.add.sprite(w/2, h*0.2+32,'dude');
	this.player.anchor.set(0.5,0);
	this.player.animations.add('run-dl',[0,1,0,2],8,true);
	this.player.animations.play('run-dl');

	this.text = game.add.text(w*0.5, h*0.5, 
	"Hurray! Now to the next level!",
	{font:'20px Tahoma', fill: '#8c993a',align:'center'});
	this.text.anchor.setTo(0.5);

	this.buttonstart = game.add.button(w/2, h*0.8, 'bigbuttons', this.nextlevel, this,3,2,3,3);
	this.buttonstart.anchor.setTo(0.5);
},

nextlevel: function(button) {
	actuallevel++;
	game.state.start('Play');
},

};

// - End -------------------------------------------------------------------------------------------

ThisGame.End.prototype = {

create: function() {
	this.player = game.add.sprite(w/2, h*0.2+32,'dude');
	this.player.anchor.set(0.5,0);
	this.player.animations.add('stand',[0],8,true);
	this.player.animations.play('stand');

	this.text = game.add.text(w*0.5, h*0.5, 
	"You Made It!\nYou Helped The Little Dude to phone home! :)\n\nThe End",
	{font:'20px Tahoma', fill: '#8c993a',align:'center'});
	this.text.anchor.setTo(0.5);

	this.buttonstart = game.add.button(w/2, h*0.8, 'bigbuttons', this.restart, this,5,4,5,5);
	this.buttonstart.anchor.setTo(0.5);
},

restart: function(button) {
	actuallevel = 0;
	game.state.start('Menu');
},

};


// - Boot ------------------------------------------------------------------------------------------

ThisGame.Boot.prototype = {
	preload: function() {game.load.image('loading', 'assets/loading.png'); },
	create: function() {game.state.start('Load');},
};

// - Load ------------------------------------------------------------------------------------------

ThisGame.Load.prototype = {

preload: function() {
	ltitle = game.add.text(w/2, h/2-30, 'loading...', { font: '20px Tahoma', fill: '#fff' });
	ltitle.anchor.setTo(0.5, 0.5);
	preloading = game.add.sprite(w*0.5, h*0.5, 'loading');
	preloading.x -= preloading.width/2;
	game.load.setPreloadSprite(preloading);

	game.load.spritesheet('bigbuttons', 'assets/bigbuttons.png', 300, 130);
	game.load.spritesheet('buttons', 'assets/buttons.png', 130, 130);
	game.load.image('title', 'assets/title.png');
	game.load.image('connect', 'assets/connect.png');
	game.load.image('fixconnect', 'assets/fixconnect.png');
	game.load.image('blueh', 'assets/blueh.png');
	game.load.image('bluev', 'assets/bluev.png');
	game.load.image('redh', 'assets/redh.png');
	game.load.image('redv', 'assets/redv.png');
	game.load.image('ic', 'assets/ic.png');
	game.load.image('board', 'assets/board.png');
	game.load.spritesheet('dude', 'assets/dude.png',32,73);

},

create: function() {
	game.state.start('Menu');
},

};

game.state.add('Boot', ThisGame.Boot);
game.state.add('Load', ThisGame.Load);
game.state.add('Menu', ThisGame.Menu);
game.state.add('Play', ThisGame.Play);
game.state.add('Win', ThisGame.Win);
game.state.add('End', ThisGame.End);
game.state.start('Boot');
