
var port = 9080;
var serverUrl = "127.0.0.1";

var http = require("http");
var path = require("path");
var fs = require("fs");

http.createServer(function (req, res) {

    var now = new Date();

    var filename = req.url || "ex1.html";
    var ext = path.extname(filename);
    var localPath = __dirname;
    var validExtensions = {
        ".html": "text/html",
        ".js": "application/javascript",
        ".css": "text/css",
        ".txt": "text/plain",
        ".jpg": "image/jpeg",
        ".gif": "image/gif",
        ".png": "image/png"
    };
    var isValidExt = validExtensions[ext];
    var vurl = req.url.split("/");

    //Logging
    console.log("filename: " + filename);
    console.log("method: " + req.method);
    console.log("url: " + req.url);
    console.log("ext: " + ext);
    console.log("localpath: " + localPath);
    console.log("path: " + path);

    for (var i = 0; i < vurl.length; i++)
    {
        console.log("vurl[" + i + "]=" + vurl[i]);
    }

    
    //Decode URL: /mathquiz/
    if ((vurl.length > 1) && (vurl[1] === 'mathquiz')) //RESTful interface
    {
        if ((vurl.length > 2) && (vurl[2] === ''))
            getFile(localPath + '/ex1.html', res, ext);
        else
        {
            getFile(localPath + '/' + vurl[2], res, ext);
        }
    }
    else if (isValidExt) {

        localPath += filename;

        fs.exists(localPath, function (exists) {
            if (exists) {
                console.log("Serving file: " + localPath);
                getFile(localPath, res, ext);
            } else {
                console.log("File not found: " + localPath);
                res.writeHead(404);
                res.end();
            }
        });

    } else {
        console.log("Invalid file extension detected: " + ext)
    }

    console.log("END");

}).listen(port, serverUrl);


function getFile(localPath, res, mimeType) {
    fs.readFile(localPath, function (err, contents) {
        if (!err) {
            res.setHeader("Content-Length", contents.length);
            res.setHeader("Content-Type", mimeType);
            res.statusCode = 200;
            res.end(contents);
        } else {
            res.writeHead(500);
            res.end();
        }
    });
}

function responseOnRequest(req, res)
{
    res.writeHead(200,
            {'Content-Type': 'text/plain; charset=UTF-8'}
    );
    var str = '';
    str += 'HTTP    version: ' + req.httpVersion + '\n';
    str += 'HTTP     method: ' + req.method + '\n';
    str += 'HTTP        url: ' + req.url + '\n\n';
    str += 'HTTP    headers: ' + JSON.stringify(req.headers) + '\n\n';
    str += 'HTTP rawHeaders: ' + req.rawHeaders + '\n';

    res.end(str);
}

function responseOnRequestError(req, res)
{
    res.writeHead(404,
            {'Content-Type': 'text/plain; charset=UTF-8'}
    );


    res.end("Error");
}