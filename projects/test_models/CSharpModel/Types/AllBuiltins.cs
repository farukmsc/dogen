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
using System;

namespace Dogen.TestModels.CSharpModel
{
    /// <summary>
    /// This is a class made up of just built-in types.
    /// </summary>
    /// <remarks>
    /// This is a remark.
    /// </remarks>
    class AllBuiltins
    {
        #region Properties
        /// <summary>
        /// A comment at property level.
        /// </summary>
        public byte ByteProperty { get; set; }
        /// <summary>
        /// A comment at property level.
        /// </summary>
        /// <remarks>
        /// This is a remark.
        /// </remarks>
        public sbyte ShortByteProperty { get; set; }
        public int IntProperty { get; set; }
        public uint UIntProperty { get; set; }
        public short ShortProperty { get; set; }
        public ushort UShortProperty { get; set; }
        public long LongProperty { get; set; }
        public ulong ULongProperty { get; set; }
        public float FloatProperty { get; set; }
        public double DoubleProperty { get; set; }
        public char CharProperty { get; set; }
        public bool BoolProperty { get; set; }
        public object ObjectProperty { get; set; }
        public string StringProperty { get; set; }
        public decimal DecimalProperty { get; set; }
        #endregion

        #region Equality
        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            if (ReferenceEquals(this, obj)) return true;
            if (obj.GetType() != this.GetType()) return false;

            var value = obj as AllBuiltins;
            if (value == null) return false;

            return
                ByteProperty == value.ByteProperty &&
                ShortByteProperty == value.ShortByteProperty &&
                IntProperty == value.IntProperty &&
                UIntProperty == value.UIntProperty &&
                ShortProperty == value.ShortProperty &&
                UShortProperty == value.UShortProperty &&
                LongProperty == value.LongProperty &&
                ULongProperty == value.ULongProperty &&
                FloatProperty == value.FloatProperty &&
                DoubleProperty == value.DoubleProperty &&
                CharProperty == value.CharProperty &&
                BoolProperty == value.BoolProperty &&
                ObjectProperty != null && value.ObjectProperty != null &&
                ObjectProperty.Equals(value.ObjectProperty) &&
                StringProperty != null && value.StringProperty != null &&
                StringProperty.Equals(value.StringProperty) &&
                DecimalProperty == value.DecimalProperty;
        }

        public static bool operator ==(AllBuiltins lhs, AllBuiltins rhs)
        {
            if (Object.ReferenceEquals(lhs, rhs))
                return true;

            if(Object.ReferenceEquals(null, lhs))
                return false;

            return (lhs.Equals(rhs));
        }

        public static bool operator !=(AllBuiltins lhs, AllBuiltins rhs)
        {
            return !(lhs == rhs);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                // Choose large primes to avoid hashing collisions
                const int HashingBase = (int) 2166136261;
                const int HashingMultiplier = 16777619;

                int hash = HashingBase;
                hash = (hash * HashingMultiplier) ^ ByteProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ ShortByteProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ IntProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ UIntProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ ShortProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ UShortProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ LongProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ ULongProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ FloatProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ DoubleProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ CharProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^ BoolProperty.GetHashCode();
                hash = (hash * HashingMultiplier) ^
                    (!ObjectProperty.ReferenceEquals(null, ObjectProperty) ? ObjectProperty.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^
                    (!StringProperty.ReferenceEquals(null, StringProperty) ? StringProperty.GetHashCode() : 0);
                hash = (hash * HashingMultiplier) ^ DecimalProperty.GetHashCode();
                return hash;
            }
       }
       #endregion
    }
}