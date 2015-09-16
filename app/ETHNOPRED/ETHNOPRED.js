//Router for the ETHNOPRED
'use strict'
module.exports = function( options ) {

    var express = require( 'express' );
    var debug = options.debug;
    var router = express.Router();
    var host = options.rootRut;
    var rootFolder = options.rootFolder;

    var dtreeJSONRut = router.route( host + 'dtree.json');
    var dtreeRut = router.route( host + 'dtree');

    //login page
    getJSONDtree.apply( dtreeJSONRut );
    postJSONDtree.apply( dtreeJSONRut, [ rootFolder ] );
    pageNavigation.apply( dtreeRut, [ "./ETHNOPRED/ETHNOPRED.ejs", "Welcome to UofA ETHNOPRED"] );

    function getJSONDtree(){
        this.get( function( req, res, next ) {
            if ( typeof async !== 'object')
                var async = require( 'async' );

            console.log("Good");

            return next();

        });
    }

    function postJSONDtree(rootFolder, viewName){
        //use multipart middleware
        var multipart = require('connect-multiparty');
        var multipartMiddleware = multipart();
        this.post( multipartMiddleware, function( req, res, next ) {
            if ( typeof async !== 'object')
                var async = require( 'async' );

            var fs = require( 'fs' );
            console.log(req.files);

            var filePath = req.files.file.path;
            console.log(filePath);

            async.waterfall([

            function readFile( callback ){

                //req.pipe( req.busboy );
                var exec = require( 'child_process' ).exec;
                var cmd = rootFolder + "/cpplib/ethnopred -i " + filePath;
                console.log(rootFolder);
                exec( cmd, function( err, stdout, stderr ) {
                  if( err ) {
                      console.log( err );
                      callback( true, "" );

                  } else {
                      var stdout = JSON.parse( stdout );
                      callback( null, stdout );
                  }
              });

            },

            ], function( err, results ) {
                if ( err ){
                  if(debug){
                    console.log( err );
                  }
                } else {
                    if( debug ){
                      console.log( debug );
                    }
                    console.log(results);
                    res.send( {data: results} );
                    return next();
                }
            });
        });
    }

    //pure page navitation without mysql request
    function pageNavigation( viewName, title ) {
        this.get( function( req, res, next ) {
            //change to the ajax url
            var ajaxUrl = req.route.path;
            if (debug){
              console.log( ajaxUrl );
            }
            res.render( viewName, {title: title, ajaxUrl: ajaxUrl} );
        });
    }

    return router;
}
