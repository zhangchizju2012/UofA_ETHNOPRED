//Router for the ETHNOPRED
'use strict'
module.exports = function( options ) {

    var express = require( 'express' );
    var debug = options.debug;
    var router = express.Router();
    var host = options.rootRut;
    var rootFolder = options.rootFolder;
    var fs = require( 'fs' );

    var dtreeJSONRut = router.route( host + 'dtree.json');
    var dtreeRut = router.route( host + 'dtree');

    //login page
    getJSONDtree.apply( dtreeJSONRut );
    postJSONDtree.apply( dtreeJSONRut );
    pageNavigation.apply( dtreeRut, [ "./ETHNOPRED/ETHNOPRED.ejs", "Welcome to UofA ETHNOPRED"] );

    function getJSONDtree(){
        this.get( function( req, res, next ) {
            if ( typeof async !== 'object')
                var async = require( 'async' );

            console.log("Good");

            return next();

        });
    }

    function postJSONDtree(){
        this.post( function( req, res, next ) {
            if ( typeof async !== 'object')
                var async = require( 'async' );

            async.waterfall([

            function readFile( callback ){
                req.pipe( req.busboy );
                req.busboy.on( 'file', function( fieldname, file, filename ) {
                    callback( null, file, filename );
                });
            },

            function writeFile( file, filename, callback ){
                //
                var filePath = "web/public/csvFile/tmp";

                var fileStream = fs.createWriteStream( filePath );

                file.pipe(fileStream);

                fileStream.on( 'close', function( err ) {

                    if ( err ) {

                        callback( true, err );

                    } else {

                        callback( null );
                    }
                });

            },


            ], function( err, results ) {
                if ( err ){

                } else {
                    console.log("Success");
                }

            });

            return next();

        });
    }

    //pure page navitation without mysql request
    function pageNavigation( viewName, title ) {
        this.get( function( req, res, next ) {
            //change to the ajax url
            var ajaxUrl =  req.route.path + '.json';
            if (debug){
              console.log( ajaxUrl );
            }
            res.render( viewName, {title: title, ajaxUrl: ajaxUrl} );
        });
    }

    return router;
}
