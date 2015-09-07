//
// ScaledView.h
//
// Copyright (c) 2001-2015 Virtual Terrain Project
// Free for all uses, see license.txt for details.
//

#pragma once

#include "vtdata/MathTypes.h"
#include "ogr_geometry.h"
#include "wx/glcanvas.h"

class vtScaledView : public wxGLCanvas
{
public:
	vtScaledView(wxWindow *parent, wxWindowID id = -1,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize, long style = 0,
		const wxString& name = _T(""));

	void SetScale(double scale);
	double GetScale();

	void ZoomToPoint(const DPoint2 &p);
	void ZoomToRect(const DRECT &geo_rect, float margin);

	// transform world space -> screen space
	void screen(const DPoint2 &p, DPoint2 &sp) const
	{
		sp = (p - m_offset)*m_dScale;
	}
	void screen(const OGRPoint *p, DPoint2 &sp) const
	{
		sp = (DPoint2(p->getX(), p->getY()) - m_offset) * m_dScale;
	}
	DPoint2 screen_delta(const DPoint2 &p) const
	{
		return p * m_dScale;
	}

	// transform screen space -> world space
	void world(const wxPoint &sp, DPoint2 &p) const
	{
		p = DPoint2(sp.x, sp.y) / m_dScale + m_offset;
	}
	DPoint2 world_delta(const DPoint2 &p)
	{
		return p / m_dScale;
	}
	DPoint2 world_delta(int pixels)
	{
		return DPoint2(pixels / m_dScale, pixels / m_dScale);
	}

	void SetColor(const RGBi &color);
	void DrawLine(const DPoint2 &p0, const DPoint2 &p1);
	void DrawLine(double p1x, double p1y, double p2x, double p2y);
	void DrawXHair(const DPoint2 &p, int pixelSize);
	void DrawRectangle(const DRECT &rect);
	void DrawPolyLine(const DLine2 &line, bool bClose);
	void DrawPolygon(const DPolygon2 &poly, bool bFill);

	void DrawOGRLinearRing(const OGRLinearRing *line, bool bCircles);
	void DrawOGRPolygon(const OGRPolygon &poly, bool bFill, bool bCircles);
	void DrawDPolygon2(const DPolygon2 &poly, bool bFill, bool bCircles);

	void GetViewParams(double &scale, DPoint2 &offset)
	{
		scale = m_dScale;
		offset = m_offset;
	}

protected:
	double	m_dScale;	// pixels per geographic unit
	DPoint2 m_offset;
};

