using System;
using System.Collections.Generic;
using System.Text;

namespace SharpboxAPI.Attributes
{
    [AttributeUsage(AttributeTargets.Class)]
    public class SharpModAttribute : Attribute
    {
        public string name = "Example";
        public string desc = "This is an example mod";
        public string author = "GScience Studio";
        public Version version = new Version(1, 0);
        public string url = "www.gscistudio.com";
    }
}
