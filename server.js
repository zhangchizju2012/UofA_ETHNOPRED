var express = require( 'express' );
var app = express();
var router = express.Router();
var path = require( 'path' );

app.ProjectName = 'ETHNOPRED';
//Set root url
app.RootRut = '/' +  app.ProjectName + '/';

app.use( express.static( path.join(__dirname, 'public')) );
app.set( 'views', path.join( __dirname, 'app') );

/* Use in-house prepated query lib*/
app.get( '/', function( req,res ){
    res.send( 'Welcome to ' + app.ProjectName + ' server!' );
});

app.RootFolder = __dirname;

//register user defined module
app.Modules = [
    'EP',
    'EP.download'
]

//extend functions for app, app.Ext
require( './config/extend.js' )( app );

//load config information
require( './config/config.js' )( app );

//load router for each module
require( './config/router.js' )( app );

require( './build/app.js' )( app );

var server = app.listen( app.Port, '0.0.0.0', function() {
   console.log( "Listening to port %s", server.address().port );
});
