'use strict'
module.exports = function( app ){
  var Module = app.Module[ 'EP.download' ];
  var Router = Module.router;
  var SNPRut = Router.SNP;
  var sampleRut = Router.sample;

  app
    .get( SNPRut, GetSNPFile );
  app
    .post( SNPRut, SendSNPFile );
  
  app
    .get( sampleRut, GetSampleFile );
  app
    .post( sampleRut, SendSampleFile );

  function GetSNPFile(){
    console.log( "Get SNP file" );
  }

  function GetSampleFile() {
    console.log( "Get sample file" );
    
  }

  function SendSNPFile( req, res, next ) {  
    console.log( req.body );
    var classifierType = req.body.classifierType;
    console.log( classifierType );
    var SNPFolder = app.RootFolder + '/public/SNP_file/SNP_list';

    var SNPFileMap = {
      'Continent' : 'Continent_149.csv',
      'Sub_continent' : 'Subcontinent_1488.csv',
      'Euro' : 'European_180.csv',
      'East_Asian' : 'EastAsian_606.csv',
      'American' : 'NorthAmerican_266.csv',
      'African' : 'African_553.csv',
      'Kenyan' : 'Kenyan_341.csv',
    }

    if ( typeof SNPFileMap[ classifierType ] === 'undefined' )
    {
      console.warn( ' [ERROR] cannot find classifier type ' ); 
    }

    var SNPFile = SNPFolder + '/' + SNPFileMap[ classifierType ];
    console.log( SNPFile );
    var fs = require( 'fs' );
    var stat = fs.statSync( SNPFile);
    var fileToSend = fs.readFileSync( SNPFile );
    res.set('Content-Type', 'text/csv');
    res.set('Content-Length', stat.size);
    res.set('Content-Disposition', SNPFile );
    console.log( fileToSend);
    res.send(fileToSend);
  }

  function SendSampleFile( req, res, next ) {
    var sampleFlieFolder = app.RootFolder + '/public/SNP_file/csv';
    var classifierType = req.body.classifierType;
    console.log( classifierType );

    var sampleFlieMap = {
      'Continent' : 'Continent.csv',
      'Sub_continent' : 'All.csv',
      'Euro' : 'European.csv',
      'East_Asian' : 'EastAsian.csv',
      'American' : 'NorthAmerican.csv',
      'African' : 'African.csv',
      'Kenyan' : 'Kenyan.csv',
    }

    if ( typeof sampleFlieMap[ classifierType ] === 'undefined' )
    {
      console.warn( ' [ERROR] cannot find classifier type ' ); 
    }

    var sampleFile = sampleFlieFolder + '/' + sampleFlieMap[ classifierType ];
    var fs = app.fs;
    var stat = fs.statSync( sampleFile );
    var fileToSend = fs.readFileSync( sampleFile );
    res.set( 'Content-Type', 'text/csv' );
    res.set( 'Content-Length', stat.size);
    res.set( 'Content-Disposition', sampleFile );
    res.send( fileToSend );
  }

}
