/* Copyright (c) 2002-2012 Croteam Ltd. 
This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

// [Cecil] Rev: Replaced all macros with constants; removed '_SE_DEMO'
ENGINE_API extern const int _SE_BUILD_MAJOR; // use new number for each released version
ENGINE_API extern const int _SE_BUILD_MINOR; // minor versions that are data-compatibile, but are not netgame-compatibile
ENGINE_API extern const char *_SE_ENGINE_BUILD; // [Cecil] Rev: Instead of _SE_BUILD_EXTRA
ENGINE_API extern const char *_SE_VER_STRING; // usually shown in server browser, etc

// [Cecil] Rev: New variable
ENGINE_API extern CTString _strEngineBuild;

