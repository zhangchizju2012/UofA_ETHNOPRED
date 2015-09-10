var allowCrossDomain = function( req, res, next ) {
    res.header('Access-Control-Allow-Origin', '*');
    res.header('Access-Control-Allow-Methods', 'GET,PUT,POST,DELETE,OPTIONS');
    res.header('Access-Control-Allow-Headers', 'Content-Type, Authorization, Content-Length, X-Requested-With');

    // intercept OPTIONS method
    if ('OPTIONS' == req.method) {
      res.send( 200 );
    }
    else {
      next();
    }
};

var express  = require( 'express' ),
    path = require( 'path' ),
    bodyParser = require( 'body-parser' ),
    app = express(),
    expressValidator = require( 'express-validator' );

/*Set EJS template Engine*/
app.set( 'views', path.join(__dirname, 'app') );
app.set( 'view engine','ejs' );

app.use( express.static( path.join(__dirname, '/bower_components')) );
app.use( bodyParser.urlencoded({ extended: true }) ); //support x-www-form-urlencoded
app.use( bodyParser() );
app.use( expressValidator() );
app.use( allowCrossDomain );

//No MySql

/* Use in-house prepated query lib*/
app.get( '/',function( req,res ){
    res.send( 'Welcome to ETHNOPRED server!' );
});

//RESTful route
var router = express.Router();

/*process.env.PORT for production*/
var port = process.env.PORT || 3001;

var options = new globalOption( __dirname ).getGlobalOption();


//Bind routing to the whole
app.use( require( './app/ETHNOPRED/ETHNOPRED.js' )( options ) );

var server = app.listen( port, '0.0.0.0', function() {
   console.log( "Listening to port %s", server.address().port );
});

function globalOption( rootFolder ){
    var instance;
    //singlton
    function init(){
        return {
            rootFolder: rootFolder,
            rootRut: '/ETHNOPRED/',
            debug: true
        }
    }

    return {
        getGlobalOption : function(){
            if ( typeof instance === "undefined" ){
                instance = new init();
            }

            return instance;
        }
    }
}
