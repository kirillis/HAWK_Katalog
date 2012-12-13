#include "students.h"

Students::Students()
{
    //ctor
    garamondRegularH1.loadFont("fonts/AGaramondPro-Regular.otf", 18);
    garamondRegularP.loadFont("fonts/AGaramondPro-Regular.otf", 14);
}

void Students::setup(int _id)
{
    id = _id;
    sqlite = new ofxSQLite(DB_NAME);
    // -- query students for all first names
    ofxSQLiteSelect dbQuery = sqlite->select("vorname, nachname, fachbereich, titel, beschreibung, image_01")
                              .from("students")
                              .where("id", id);

    dbQuery.execute().begin();

    // process query result, store names
    first_name = dbQuery.getString(0);
    last_name = dbQuery.getString(1);
    fachbereich = dbQuery.getString(2);
    titel = dbQuery.getString(3);
    beschreibung = dbQuery.getString(4);
    image_01 = dbQuery.getString(5);


    // load image
    if(!projectImage01.loadImage(IMAGE_DIR "/" + image_01))
    {
        cout << "error loading image: " << image_01 << endl;
    }

}

void Students::drawInfo(int _x, int _y)
{
    // set position
    x = _x;
    y = _y;

    // bilder rahmen hoehe/breite
    double rahmen = 400;
    int centerXWindow = ofGetWidth() / 2;
    int centerYWindow = ofGetHeight() / 2;

    // draw info
    garamondRegularH1.drawString( first_name + " " + last_name + " (" + fachbereich + ")", 50, 100 );
    garamondRegularH1.drawString( titel, 50, ofGetHeight() - 150 );

    string beschreibungWrapped = wrapString(beschreibung, 800);
    garamondRegularP.drawString(beschreibungWrapped, 50, ofGetHeight() - 125 );

    ofSetLineWidth(2);
    ofLine(0, centerYWindow - rahmen/2 -1, ofGetWidth(), centerYWindow - rahmen/2 -1);
    ofLine(0, centerYWindow + rahmen/2 +1, ofGetWidth(), centerYWindow + rahmen/2 +1);
    ofSetLineWidth(1);

    //draw image01
    // set color to white for tint-free images
    ofSetColor(255,255,255);
    double imageWidth = projectImage01.width;
    double imageHeight = projectImage01.height;
    int ratio = imageWidth / imageHeight;

    if(ratio <= 1)
    {
        // hoeher als breit oder quadratisch
        double conversion = rahmen / imageHeight;
        int resizedImageWidth = imageWidth * conversion;
        int resizedImageHeight = imageHeight * conversion;
        // draw image in center if screen
        projectImage01.draw(centerXWindow - resizedImageWidth/2, centerYWindow - resizedImageHeight/2, resizedImageWidth , resizedImageHeight );
    }
    else
    {
        // breiter als hoch
        double conversion = rahmen / imageWidth;
        int resizedImageWidth = imageWidth * conversion;
        int resizedImageHeight = imageHeight * conversion;
        // draw image in center if screen
        projectImage01.draw(centerXWindow - resizedImageWidth/2, centerYWindow - resizedImageHeight/2, resizedImageWidth , resizedImageHeight );
    }
}

// count number of records in DB
int Students::countAll(std::string fb)
{
    ofxSQLite* sqlite = new ofxSQLite(DB_NAME);
    // count entries
    ofxSQLiteSelect selectCount = sqlite->select("count(*) as total")
                                    .from("students")
                                    .where("fachbereich", fb)
                                    .execute().begin();
    return selectCount.getInt();
}

// return array of student IDs
int* Students::getStudentIds(std::string fb)
{
    ofxSQLite* sqlite = new ofxSQLite(DB_NAME);
    // count entries

    int count = Students::countAll(fb);

    // make query for all IDs
    ofxSQLiteSelect sel = sqlite->select("id")
                          .from("students")
                          .where("fachbereich", fb)
                          .order("id", " ASC ")
                          .execute().begin();

    // create new int studentIdArray
    int *studentIdArray = new int[count];
    int i = 0;
    // put IDs from SQL query into array
    while(sel.hasNext())
    {
        int id = sel.getInt();
        cout << "(getStudentIds) put IDs into array, id: " << id << endl;
        studentIdArray[i] = id;
        i++;
        sel.next();
    }
    // return int array with IDs
    return studentIdArray;

}

// function to wrap text string into box, input textstring and box width (from c++ forums), returns textstring with added '/n' for formatting
string Students::wrapString(string text, int width)
{

    string typeWrapped = "";
    string tempString = "";
    vector <string> words = ofSplitString(text, " ");
    for(int i=0; i<words.size(); i++)
    {
        string wrd = words[i];
        // if we aren't on the first word, add a space
        if (i > 0)
        {
            tempString += " ";
        }
        tempString += wrd;
        int stringwidth = garamondRegularP.stringWidth(tempString);
        if(stringwidth >= width)
        {
            typeWrapped += "\n";
            tempString = wrd;       // make sure we're including the extra word on the next line
        }
        else if (i > 0)
        {
            // if we aren't on the first word, add a space
            typeWrapped += " ";
        }
        typeWrapped += wrd;
    }
    return typeWrapped;
}

Students::~Students()
{
    //dtor
}