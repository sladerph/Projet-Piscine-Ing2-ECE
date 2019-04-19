#ifndef SVGFILE_H_INCLUDED
#define SVGFILE_H_INCLUDED

/// \file
/// \brief
/// \author

#include <string>
#include <fstream>
#include <set>

constexpr char defcol[] = "black";

class Svgfile
{
    public:
        Svgfile(std::string _filename = "output.svg", int _width=1000, int _height=800);
        ~Svgfile();

        void addDisk(double x, double y, double r, std::string color=defcol);
        void addCircle(double x, double y, double r, double ep, std::string color=defcol);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill,
                          double thickness, std::string colorStroke);
        void addTriangle(double x1, double y1, double x2, double y2,
                         double x3, double y3, std::string colorFill=defcol);
        void addLine(double x1, double y1, double x2, double y2, std::string color=defcol, int strokeWidth = 1);
        void addCross(double x, double y, double span, std::string color=defcol);

        void addText(double x, double y, std::string text, std::string color=defcol, std::string align = "start");
        void addText(double x, double y, double val, std::string color=defcol, std::string align = "start");

        void addGrid(double span=100.0, bool numbering=true, std::string color="lightgrey");

        static std::string makeRGB(int r, int g, int b);

        int getWidth() const {return m_width;};
        int getHeight() const {return m_height;};

        /// Type non copiable
        Svgfile(const Svgfile&) = delete;
        Svgfile& operator=(const Svgfile&) = delete;

    private:
        std::string m_filename;
        std::ofstream m_ostrm;
        int m_width;
        int m_height;

        // Pour éviter les ouverture multiples
        static std::set<std::string> s_openfiles;
};

struct FileConf {
    std::string filename = "";
    int width;
    int height;
    bool hasGrid;
};

#endif // SVGFILE_H_INCLUDED



