// This file is available under GNU Affero General Public License.
// See the LICENSE file of the project for more detail.

// This file is powered by TinyXML2 and requires TinyXML2 library
// to compile and work.

#include "tinyxml2-master/tinyxml2.h"
#include <vector>
#include <memory>
#include <string>
#include <cmath>
#include <sstream>

using namespace tinyxml2;
using namespace std;

const double PI = acos(-1);
const int CENTER_DIS = 350, CENTER_POS = 512, VERTEX_RADIUS = 20, STROKE_WIDTH = 4;

inline double Deg2Rad(double deg)
{
    return deg * PI / 180;
}

// Test function, not used in the final version
void HaveFun()
{
    vector<int> vec = {1, 91, 9810};

    XMLDocument xmlDoc;

    XMLNode * pRoot = xmlDoc.NewElement("Root");
    xmlDoc.InsertFirstChild(pRoot);

    XMLElement * pIElement = xmlDoc.NewElement("IntValue");
    pIElement->SetText(114514);
    pRoot->InsertEndChild(pIElement);

    XMLElement * pBElement = xmlDoc.NewElement("Bog");
    pBElement->SetAttribute("1", "Bog");
    pBElement->SetAttribute("2", "Cog");
    pBElement->SetAttribute("3", "Dog");
    pRoot->InsertEndChild(pBElement);

    XMLElement * pLElement = xmlDoc.NewElement("List");
    for (const auto& i: vec)
    {
        XMLElement * pVecElement = xmlDoc.NewElement("Item");
        pVecElement->SetText(i);

        pLElement->InsertEndChild(pVecElement);
    }
    pRoot->InsertEndChild(pLElement);

    xmlDoc.SaveFile("D:\\workspace\\city-traffic\\SavedData.xml");
}

// Draw a circle for vertices
void AddCircle(XMLDocument* pDoc, XMLNode* pRoot, int cx, int cy, int r, string stroke, int width, string fillcol)
{
    XMLElement* pCircle = pDoc->NewElement("circle");
    pCircle->SetAttribute("cx", to_string(cx).c_str());
    pCircle->SetAttribute("cy", to_string(cy).c_str());
    pCircle->SetAttribute("r", to_string(r).c_str());
    pCircle->SetAttribute("stroke", stroke.c_str());
    pCircle->SetAttribute("stroke-width", to_string(width).c_str());
    pCircle->SetAttribute("fill", fillcol.c_str());
    pRoot->InsertEndChild(pCircle);
}

// Draw the graph
// This function will need to be completed when graph api is ready
void DrawGraph(XMLDocument* pDoc, XMLNode* pRoot, int nodeCount)
{
    double rotateDeg = 360 / nodeCount;
    for (int i = 0; i < nodeCount; ++i)
    {
        int cx = int(CENTER_POS + CENTER_DIS * cos(Deg2Rad(i * rotateDeg)));
        int cy = int(CENTER_POS + CENTER_DIS * sin(Deg2Rad(i * rotateDeg)));
        AddCircle(pDoc, pRoot, cx, cy, VERTEX_RADIUS, "#999999", STROKE_WIDTH, "#EEEEEE");
    }
}

// Draw cars
// Will be done in the future
void DrawCars();

int main()
{

    XMLDocument doc;
    XMLNode* pRoot = doc.NewElement("html");
    doc.InsertFirstChild(pRoot);

    XMLNode* pBody = doc.NewElement("body");
    pRoot->InsertEndChild(pBody);

    XMLElement* pSVG = doc.NewElement("svg");
    pSVG->SetAttribute("xmlns", "https://github.com/maperog");
    pSVG->SetAttribute("version", "1.0b");
    pSVG->SetAttribute("width", "1024");
    pSVG->SetAttribute("height", "1024");
    pBody->InsertEndChild(pSVG);

    XMLElement* pText = doc.NewElement("h1");
    pText->SetText("City Traffic Emulator");
    pBody->InsertFirstChild(pText);

    //AddCircle(&doc, pSVG, 100, 50, 15, "#999999", 4, "#EEEEEE");
    DrawGraph(&doc, pSVG, 15);

    doc.SaveFile("D:\\workspace\\city-traffic\\data1.xml");
    doc.SaveFile("D:\\workspace\\city-traffic\\data1.html");

    return 0;
}
