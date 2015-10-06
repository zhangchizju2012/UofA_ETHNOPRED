var express = require( 'express' );
var app = express();
var router = express.Router();
var path = require( 'path' );

app.ProjectName = 'ETHNOPRED';
//Set root url
app.RootRut = '/' +  app.ProjectName + '/';
//app.use( '/app', router );

app.use( express.static( path.join(__dirname, 'public')) );
app.set( 'views', path.join( __dirname, 'app') );

/* Use in-house prepated query lib*/
app.get( ( '/' + app.ProjectName ) + function( req,res ){
    res.send( 'Welcome to EP server!' );
});

//register user defined module
app.Modules = [
    'EP'
]

//extend functions for app, app.Ext
require( './app/extend.js')( app );

//load config information
require( './app/config.js')( app );

//load router for each module
require( './app/router.js')( app );

//load helper for each module
require( './app/helper.js')( app );

require( './build/app.js' )( app );

var server = app.listen( app.Port, '0.0.0.0', function() {
   console.log( "Listening to port %s", server.address().port );
});