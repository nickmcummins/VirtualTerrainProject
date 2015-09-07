//
// ScaledView.cpp
//
// Copyright (c) 2001-2013 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <algorithm>

#include "vtdata/vtLog.h"
#include "ScaledView.h"
#include "Builder.h"
#include "vtdata/Triangulate.h"

///////////////////////////////////////////////////////////////////////

vtScaledView::vtScaledView(wxWindow *parent, wxWindowID id, const wxPoint& pos,
						 const wxSize& size, long style, const wxString& name) :
	wxGLCanvas(parent, id, NULL, pos, size, style, name )
{
	m_offset.Set(0, 0);
	m_dScale = 1.0f;
}

void vtScaledView::ZoomToRect(const DRECT &geo_rect, float margin)
{
	VTLOG(" ZoomToRect LRTB(%lg, %lg, %lg, %lg)\n", geo_rect.left, geo_rect.right, geo_rect.top, geo_rect.bottom);

	wxRect client;
	GetClientSize(&client.width, &client.height);

	// safety check: if the data is a single point, back out slightly
	DRECT rect = geo_rect;
	if (rect.Width() == 0)
		rect.Grow(0.25, 0);
	if (rect.Height() == 0)
		rect.Grow(0, 0.25);

	// scale is pixels/coordinate unit
	DPoint2 scale;
	scale.x = (float) client.GetWidth() / rect.Width();
	scale.y = (float) client.GetHeight() / rect.Height();
	m_dScale = std::min(scale.x, scale.y);
	m_dScale *= (1.0f - margin);

	DPoint2 center;
	rect.GetCenter(center);
	ZoomToPoint(center);
}

void vtScaledView::ZoomToPoint(const DPoint2 &p)
{
	DPoint2 offset;
	screen(p, offset);

	int w, h;
	GetClientSize(&w, &h);
	offset.x -= (w / 2);
	offset.y -= (h / 2);

}

void vtScaledView::SetScale(double scale)
{
	m_dScale = scale;
	Refresh();
}

double vtScaledView::GetScale()
{
	return m_dScale;
}

void vtScaledView::DrawLine(const DPoint2 &p0, const DPoint2 &p1)
{
	glBegin(GL_LINES);
	glVertex2d(p0.x, p0.y);
	glVertex2d(p1.x, p1.y);
	glEnd();
}

void vtScaledView::SetColor(const RGBi &color)
{
	glColor3f(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}

void vtScaledView::DrawLine(double p1x, double p1y, double p2x, double p2y)
{
	glBegin(GL_LINES);
	glVertex2d(p1x, p1y);
	glVertex2d(p2x, p2y);
	glEnd();
}

void vtScaledView::DrawXHair(const DPoint2 &p, int pixelSize)
{
	DPoint2 hairsize = world_delta(pixelSize);
	glBegin(GL_LINES);
	glVertex2d(p.x - hairsize.x, p.y);
	glVertex2d(p.x + hairsize.x, p.y);
	glVertex2d(p.x, p.y - hairsize.y);
	glVertex2d(p.x, p.y + hairsize.y);
	glEnd();
}

void vtScaledView::DrawRectangle(const DRECT &rect)
{
	glBegin(GL_LINE_STRIP);
	glVertex2d(rect.left, rect.top);
	glVertex2d(rect.right, rect.top);
	glVertex2d(rect.right, rect.bottom);
	glVertex2d(rect.left, rect.bottom);
	glVertex2d(rect.left, rect.top);
	glEnd();
}

void vtScaledView::DrawPolyLine(const DLine2 &dline, bool bClose)
{
	glBegin(GL_LINE_STRIP);
	for (uint i = 0; i < dline.GetSize(); i++)
		glVertex2d(dline[i].x, dline[i].y);
	glEnd();
}

void vtScaledView::DrawPolygon(const DPolygon2 &poly, bool bFill)
{
	// just draw each ring
	for (uint ring = 0; ring < poly.size(); ring++)
		DrawPolyLine(poly[ring], true);

	// TODO: support filled polygons; could use CallTriangle as below
}

void vtScaledView::DrawOGRLinearRing(const OGRLinearRing *line, bool bCircles)
{
	int i, size = line->getNumPoints();
	if (size < 2)
		return;

	glBegin(GL_LINE_STRIP);
	OGRPoint op;
	for (i = 0; i < size; i++)
	{
		line->getPoint(i, &op);
		glVertex2d(op.getX(), op.getY());
	}
	line->getPoint(0, &op);
	glVertex2d(op.getX(), op.getY());
	glEnd();

	// TODO? "bCircles"
}

void vtScaledView::DrawOGRPolygon(const OGRPolygon &poly, bool bFill,
								  bool bCircles)
{
	if (bFill)
	{
		// TODO
	}
	else
	{
		// just draw each ring
		DrawOGRLinearRing(poly.getExteriorRing(), bCircles);

		for (int ring = 0; ring < poly.getNumInteriorRings(); ring++)
			DrawOGRLinearRing(poly.getInteriorRing(ring), bCircles);
	}
}

void vtScaledView::DrawDPolygon2(const DPolygon2 &poly, bool bFill,
								  bool bCircles)
{
	static wxPoint s_box[5];

	if (bFill)
	{
		// tessellate.  we could also draw these as solid triangles.
		DLine2 result;
		CallTriangle(poly, result);
		int tcount = result.GetSize()/3;
		for (int j = 0; j < tcount; j++)
		{
			const DPoint2 &p1 = result[j*3+0];
			const DPoint2 &p2 = result[j*3+1];
			const DPoint2 &p3 = result[j*3+2];
			DrawLine(p1, p2);
			DrawLine(p2, p3);
			DrawLine(p3, p1);
		}
	}
	else
	{
		// just draw each ring
		for (uint ring = 0; ring < poly.size(); ring++)
		{
			DrawPolyLine(poly[ring], true);
		}
		// TODO? "bCircles"
	}
}

