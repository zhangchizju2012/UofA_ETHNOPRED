'use strict'
module.exports = function( app ){

  console.log( app );
  function SendFile( req, res, next ) {  
    console.log( 'running' );
    var reqData = req.body.data;
    var classifierType = JSON.parse( reqData ).classifierType;
    var SNPFolder = app.RootFolder + '/public/SNP_file/SNP_list';

    var SNPFileMap = {
      'Continent' : 'Continent_149.csv',
      'Sub_continent' : 'Subcontinent_1488.csv',
      'Euro' : 'European_180.csv',
      'East_Asian' : 'EastAsian_606.csv',
      'American' : 'NorthAmerican_266.csv',
      'African' : 'African_553.csv',
      'Kenyann' : 'Kenyan_341.csv',
    }

    if ( typeof SNPFileMap[ classifierType ] === 'undefined' )
    {
      console.warn( ' [ERROR] cannot find classifier type ' ); 
    
    }
    var SNPFile = SNPFolder + '/' + SNPFileMap[ classifierType ];
    console.log( SNPFile );
    res.sendFile( SNPFile );
  }

}
