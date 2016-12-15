// -*- mode: csharp; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
//
// Copyright (C) 2012-2015 Marco Craveiro <marco.craveiro@gmail.com>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
// MA 02110-1301, USA.
//
using System.Collections.Generic;
using System;
using System.Collections;

namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// Generates sequences of OneProperty.
    /// </summary>
    public static class OnePropertySequenceGenerator
    {
		#region Factory methods
		static int CreateInt(uint position)
		{
			return Convert.ToInt32(position);
		}

		static internal OneProperty Create(uint position)
		{
			var result = new OneProperty();
			result.Property = CreateInt(position + 0);
			return result;
		}
		#endregion

		#region Enumerator
		private class OnePropertyEnumerator : IEnumerator, IEnumerator<OneProperty>, IDisposable 
		{
			#region Properties
			private uint _position;
			private readonly OneProperty _current;
			#endregion

			#region IDisposable
			public void Dispose()
			{
			}
			#endregion

			#region IEnumerator implementation
			public bool MoveNext()
			{
				++_position;
				Create(_position);
				return true;
			}

			public void Reset()
			{
				_position = 0;
				Create(_position);
			}

			public object Current {
				get
				{
					return _current;
				}
			}

			OneProperty IEnumerator<OneProperty>.Current                                                
			{                                                                           
				get                                                                     
				{                                                                       
					return _current;                                           
				}                                                                       
			}                                                                           
			#endregion

			public OnePropertyEnumerator()
			{
				_current = OnePropertySequenceGenerator.Create(_position);
			}
		}
		#endregion

		#region Enumerable
		private class OnePropertyEnumerable : IEnumerable, IEnumerable<OneProperty>
		{
			#region IEnumerable implementation
			public IEnumerator GetEnumerator()
			{
				return new OnePropertyEnumerator();
			}

			IEnumerator<OneProperty> IEnumerable<OneProperty>.GetEnumerator()
			{
				return new OnePropertyEnumerator();
			}
			#endregion
		}
		#endregion

		static public IEnumerable<OneProperty> Sequence()
		{
			return new OnePropertyEnumerable();
		}
    }
}
