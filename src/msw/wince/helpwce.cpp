/////////////////////////////////////////////////////////////////////////////
// Name:        helpwce.h
// Purpose:     Help system: Windows CE help implementation
// Author:      Julian Smart
// Modified by:
// Created:     2003-07-12
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:   	wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
    #pragma implementation "helpwce.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_HELP

#include "wx/filefn.h"
#include "wx/msw/wince/helpwce.h"

#ifndef WX_PRECOMP
    #include "wx/intl.h"
#endif

#include "wx/msw/private.h"
#include "wx/msw/missing.h"

IMPLEMENT_DYNAMIC_CLASS(wxWinceHelpController, wxHelpControllerBase)

bool wxWinceHelpController::Initialize(const wxString& filename)
{
    m_helpFile = filename;
    return TRUE;
}

bool wxWinceHelpController::LoadFile(const wxString& file)
{
    if (!file.IsEmpty())
        m_helpFile = file;
    return TRUE;
}

bool wxWinceHelpController::DisplayContents()
{
    return ViewURL();
}

// Use topic
bool wxWinceHelpController::DisplaySection(const wxString& section)
{
    return ViewURL(section);
}

// Use context number
bool wxWinceHelpController::DisplaySection(int section)
{
    return TRUE;
}

bool wxWinceHelpController::DisplayContextPopup(int contextId)
{
    return TRUE;
}

bool wxWinceHelpController::DisplayTextPopup(const wxString& text, const wxPoint& pos)
{
    return TRUE;
}

bool wxWinceHelpController::DisplayBlock(long block)
{
    return TRUE;
}

bool wxWinceHelpController::KeywordSearch(const wxString& k)
{
    return TRUE;
}

bool wxWinceHelpController::Quit()
{
    return TRUE;
}

// Append extension if necessary.
wxString wxWinceHelpController::GetValidFilename(const wxString& file) const
{
    wxString path, name, ext;
    wxSplitPath(file, & path, & name, & ext);

    wxString fullName;
    if (path.IsEmpty())
        fullName = name + wxT(".htm");
    else if (path.Last() == wxT('\\'))
        fullName = path + name + wxT(".htm");
    else
        fullName = path + wxT("\\") + name + wxT(".htm");
    return fullName;
}

// View URL
bool wxWinceHelpController::ViewURL(const wxString& topic)
{
    if (m_helpFile.IsEmpty()) return FALSE;
    
    wxString url( wxT("file:") + GetValidFilename(m_helpFile) );
    if (!topic.IsEmpty())
        url = url + wxT("#") + topic;

    return CreateProcess(wxT("peghelp.exe"),
        url, NULL, NULL, FALSE, 0, NULL,
        NULL, NULL, NULL) != 0 ;
}

#endif // wxUSE_HELP

