/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013 CERN
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include <geometry/shape_line_chain.h>
#include <geometry/shape_circle.h>

using namespace std;
using boost::optional;

bool SHAPE_LINE_CHAIN::Collide( const VECTOR2I& aP, int aClearance ) const
{
	assert( false );
	return false;
}


bool SHAPE_LINE_CHAIN::Collide( const BOX2I& aBox, int aClearance ) const
{
	assert( false );
	return false;
}


bool SHAPE_LINE_CHAIN::Collide( const SEG& aSeg, int aClearance ) const
{
	BOX2I box_a( aSeg.a, aSeg.b - aSeg.a );
	BOX2I::ecoord_type dist_sq = (BOX2I::ecoord_type) aClearance * aClearance;

	for( int i = 0; i < SegmentCount() ;i++ )
	{
		const SEG& s = CSegment( i );
		BOX2I box_b( s.a, s.b - s.a );
	
		BOX2I::ecoord_type d = box_a.SquaredDistance ( box_b );

		if( d < dist_sq )
		{
			if( s.Collide( aSeg, aClearance ) )
				return true;
		}
	}

	return false;
}

const SHAPE_LINE_CHAIN SHAPE_LINE_CHAIN::Reverse() const 
{
	SHAPE_LINE_CHAIN a( *this );
	reverse( a.m_points.begin(), a.m_points.end() );
	a.m_closed = m_closed;

	return a;
}

	
int SHAPE_LINE_CHAIN::Length() const
{
	int l = 0;
	for( int i = 0; i < SegmentCount(); i++ )
		l += CSegment( i ).Length();

	return l;
}


void SHAPE_LINE_CHAIN::Replace( int aStartIndex, int aEndIndex, const VECTOR2I& aP )
{
	if( aEndIndex < 0 )
		aEndIndex += PointCount();
	if( aStartIndex < 0 )
		aStartIndex += PointCount();

	if( aStartIndex == aEndIndex )
		m_points [aStartIndex] = aP;
	else
	{
		m_points.erase( m_points.begin() + aStartIndex + 1, m_points.begin() + aEndIndex + 1 );
		m_points[aStartIndex] = aP;
	}
}


void SHAPE_LINE_CHAIN::Replace( int aStartIndex, int aEndIndex, const SHAPE_LINE_CHAIN& aLine )
{
	if( aEndIndex < 0 )
		aEndIndex += PointCount();
	if( aStartIndex < 0 )
		aStartIndex += PointCount();

	m_points.erase( m_points.begin() + aStartIndex, m_points.begin() + aEndIndex + 1 );
	m_points.insert( m_points.begin() + aStartIndex, aLine.m_points.begin(), aLine.m_points.end() );
}


void SHAPE_LINE_CHAIN::Remove( int aStartIndex, int aEndIndex )
{
	if(aEndIndex < 0)
		aEndIndex += PointCount();
	if(aStartIndex < 0)
		aStartIndex += PointCount();

	m_points.erase( m_points.begin() + aStartIndex, m_points.begin() + aEndIndex + 1 );
}


int SHAPE_LINE_CHAIN::Distance( const VECTOR2I& aP ) const
{
	int d = INT_MAX;
	for( int s = 0; s < SegmentCount(); s++ )
		d = min( d, CSegment( s ).Distance( aP ) );

	return d;
}


int SHAPE_LINE_CHAIN::Split( const VECTOR2I& aP )
{
	int ii = -1;
	int min_dist = 2;

	ii = Find( aP );

	if( ii >= 0 )
		return ii;

	for( int s = 0; s < SegmentCount(); s++ )
	{
		const SEG seg = CSegment( s );
		int dist = seg.Distance( aP );

		// make sure we are not producing a 'slightly concave' primitive. This might happen
		// if aP lies very close to one of already existing points.			
		if( dist < min_dist && seg.a != aP && seg.b != aP )
		{
			min_dist = dist;
			ii = s;
		}
	}

	if( ii >= 0 )
	{
		m_points.insert( m_points.begin() + ii + 1, aP );

		return ii + 1;
	}

	return -1;
}


int SHAPE_LINE_CHAIN::Find( const VECTOR2I& aP ) const
{
	for( int s = 0; s< PointCount(); s++ )
		if( CPoint( s ) == aP )
			return s;

	return -1;
}


const SHAPE_LINE_CHAIN SHAPE_LINE_CHAIN::Slice( int aStartIndex, int aEndIndex ) const
{
	SHAPE_LINE_CHAIN rv;
	
	if( aEndIndex < 0 )
		aEndIndex += PointCount();
	if( aStartIndex < 0 )
		aStartIndex += PointCount();

	for( int i = aStartIndex; i <= aEndIndex; i++ )
		rv.Append( m_points[i] );

	return rv;
}


struct compareOriginDistance
{
	compareOriginDistance( VECTOR2I& aOrigin ):
		m_origin( aOrigin ) {};

	bool operator()( const SHAPE_LINE_CHAIN::Intersection& aA,
	                 const SHAPE_LINE_CHAIN::Intersection& aB )
	{
		return ( m_origin - aA.p ).EuclideanNorm() < ( m_origin - aB.p ).EuclideanNorm();
	}

	VECTOR2I m_origin;
};

		
int SHAPE_LINE_CHAIN::Intersect( const SEG& aSeg, Intersections& aIp ) const
{
	for( int s = 0; s < SegmentCount(); s++ )
	{
		OPT_VECTOR2I p = CSegment( s ).Intersect( aSeg );
		if( p )
		{
			Intersection is;
			is.our = CSegment( s );
			is.their = aSeg;
			is.p = *p;
			aIp.push_back( is );
		}
	}

	compareOriginDistance comp( aSeg.a );
	sort( aIp.begin(), aIp.end(), comp );

	return aIp.size();
}


int SHAPE_LINE_CHAIN::Intersect( const SHAPE_LINE_CHAIN& aChain, Intersections& aIp ) const
{
    BOX2I bb_other = aChain.BBox();
	
	for ( int s1 = 0; s1 < SegmentCount(); s1++ )
	{
		const SEG& a = CSegment( s1 );
		const BOX2I bb_cur( a.a, a.b - a.a );

		if( !bb_other.Intersects( bb_cur ) )
			continue;

		for( int s2 = 0; s2 < aChain.SegmentCount(); s2++ )
		{
			const SEG& b = aChain.CSegment( s2 );
			Intersection is;
			
			if( a.Collinear( b ) )
			{
				if( a.Contains( b.a ) ) { is.p = b.a; aIp.push_back( is ); }
				if( a.Contains( b.b ) ) { is.p = b.b; aIp.push_back( is ); }
				if( b.Contains( a.a ) ) { is.p = a.a; aIp.push_back( is ); }
				if( b.Contains( a.b ) ) { is.p = a.b; aIp.push_back( is ); }
			}
			else
			{
				OPT_VECTOR2I p = a.Intersect( b );
				
				if( p )
				{
					is.p = *p;
					is.our = a;
					is.their = b;
					aIp.push_back( is );
				}
			}
		}
	}
	
	return aIp.size();

	for( int s1 = 0; s1 < SegmentCount(); s1++ )
	{
		for( int s2 = 0; s2 < aChain.SegmentCount(); s2++ )
		{
			const SEG& a = CSegment( s1 );
			const SEG& b = aChain.CSegment( s2 );
			OPT_VECTOR2I p = a.Intersect( b );
			Intersection is;
			
			if( p )
			{
				is.p = *p;
				is.our = a;
				is.their = b;
				aIp.push_back( is );
			}
			else if( a.Collinear( b ) )
			{
				if( a.a != b.a && a.a != b.b && b.Contains( a.a ) )
				{
					is.p = a.a;
					is.our = a;
					is.their = b;
					aIp.push_back( is );
				}
				else if( a.b != b.a && a.b != b.b && b.Contains( a.b ) )
				{
					is.p = a.b;
					is.our = a;
					is.their = b;
					aIp.push_back( is );
				}

			}
		}
	}

	return aIp.size();
}


int SHAPE_LINE_CHAIN::PathLength( const VECTOR2I& aP ) const
{
	int sum = 0;
	for( int i = 0; i < SegmentCount(); i++ )
	{
		const SEG seg = CSegment( i );
		int d = seg.Distance( aP );

		if( d <= 1 )
		{
			sum += ( aP - seg.a ).EuclideanNorm();
			return sum;
		}
		else
			sum += seg.Length();
	}

	return -1;
}


bool SHAPE_LINE_CHAIN::PointInside( const VECTOR2I& aP ) const
{
	if( !m_closed || SegmentCount() < 3 )
		return false;

	int cur = CSegment(0).Side( aP );

	if( cur == 0 )
		return false;

	for( int i = 1; i < SegmentCount(); i++ )
	{
		const SEG s = CSegment( i );

		if( aP == s.a || aP == s.b ) // edge does not belong to the interior!
			return false;

		if( s.Side(aP) != cur )
			return false;
    }

	return true;
}
	

bool SHAPE_LINE_CHAIN::PointOnEdge( const VECTOR2I& aP ) const
{
	if( SegmentCount() < 1 )
		return m_points[0] == aP;

	for( int i = 1; i < SegmentCount(); i++ )
	{
		const SEG s = CSegment( i );
		
		if( s.a == aP || s.b == aP )
			return true;

		if( s.Distance(aP) <= 1 )
			return true;
	}

	return false;
}


const optional<SHAPE_LINE_CHAIN::Intersection> SHAPE_LINE_CHAIN::SelfIntersecting() const
{
	for( int s1 = 0; s1 < SegmentCount(); s1++ )
	{
		for( int s2 = s1 + 1; s2 < SegmentCount(); s2++ )
		{
			const VECTOR2I s2a = CSegment( s2 ).a, s2b = CSegment( s2 ).b;
			if( s1 + 1 != s2 && CSegment( s1 ).Contains( s2a ) )
			{
				Intersection is;
				is.our = CSegment( s1 );
				is.their = CSegment( s2 );
				is.p = s2a;
				return is;
			}
			else if( CSegment( s1 ).Contains(s2b ) )
			{
				Intersection is;
				is.our = CSegment( s1 );
				is.their = CSegment( s2 );
				is.p = s2b;
				return is;
			}
			else
			{
				OPT_VECTOR2I p = CSegment( s1 ).Intersect( CSegment( s2 ), true );
			
				if( p )
				{
					Intersection is;
					is.our = CSegment( s1 );
					is.their = CSegment( s2 );
					is.p = *p;
					return is;
				}
			}
		}
	}

	return optional<Intersection>();
}
		

SHAPE_LINE_CHAIN& SHAPE_LINE_CHAIN::Simplify()
{
	vector<VECTOR2I> pts_unique;
		
	if( PointCount() < 2 )
	{
		return *this;
	}
	else if( PointCount() == 2 )
	{
		if( m_points[0] == m_points[1] )
			m_points.erase( m_points.end() );

		return *this;
	}

	int i = 0;
	int np = PointCount();
		
	// stage 1: eliminate duplicate vertices
	while ( i < np )
	{
		int j = i + 1;
		while( j < np && CPoint(i) == CPoint( j ) )
			j++;

		pts_unique.push_back( CPoint( i ) );
		i = j;
	}

	m_points.clear();
	np = pts_unique.size();

	i = 0;
	// stage 1: eliminate collinear segments
	while( i < np - 2 )
	{
		const VECTOR2I p0 = pts_unique[i];
		const VECTOR2I p1 = pts_unique[i+1];
		int n = i;

		while( n < np - 2 && SEG( p0, p1 ).LineDistance( pts_unique[n + 2] ) <= 1 )
			n++;
		
		m_points.push_back( p0 );
		if( n > i )
			i = n;

		if( n == np )
		{
			m_points.push_back( pts_unique[n - 1] );
			return *this;
		}

		i++;
	}

	if( np > 1 )
		m_points.push_back( pts_unique[np - 2] );

	m_points.push_back( pts_unique[np - 1] );

	return *this;
}


const VECTOR2I SHAPE_LINE_CHAIN::NearestPoint( const VECTOR2I& aP ) const
{
	int min_d = INT_MAX;
	int nearest = 0;
	for ( int i = 0; i < SegmentCount(); i++ )
	{
		int d = CSegment( i ).Distance( aP );
		if( d < min_d )
		{
			min_d = d;
			nearest = i;
		}
	}

	return CSegment( nearest ).NearestPoint( aP );
}


const string SHAPE_LINE_CHAIN::Format() const
{
	stringstream ss;

	ss << m_points.size() << " " << ( m_closed ? 1 : 0 ) << " " ;

	for( int i = 0; i < PointCount(); i++ )
		ss << m_points[i].x << " " << m_points[i].y << " ";// Format() << " ";
	
	return ss.str();
}
