using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Asteroids {

	class VariableSystem {

		private List<Variable> m_variables = null;
		private List<string> m_categories = null;

		// create an empty variable system
		public VariableSystem() {
			m_variables = new List<Variable>();
			m_categories = new List<string>();
		}

		// add a category string to the list of categories
		public int addCategory(string category) {
			if(category == null || category.Length == 0) { return Variable.NO_CATEGORY; }
			if(!m_categories.Contains(category)) {
				m_categories.Add(category);
				return m_categories.Count() - 1;
			}
			else {
				return m_categories.IndexOf(category);
			}
		}

		// get the index of a category string within the collection of categories
		public int indexOfCategory(string category) {
			if(category == null || m_categories.Count() == 0) { return -1; }

			for(int i=0;i<m_categories.Count();i++) {
				if(category.Equals(m_categories[i], StringComparison.OrdinalIgnoreCase)) {
					return i;
				}
			}

			return -1;
		}

		// get a category from a specific index
		public string categoryAt(int index) {
			if(index < 0 || index >= m_categories.Count()) { return null; }
			return m_categories[index];
		}

		// get the number of variables
		public int size() {
			return m_variables.Count();
		}

		// check if a variable is contained in the collection based on its id
		public bool contains(string id) {
			if(id == null) { return false; }

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase)) {
					return true;
				}
			}
			return false;
		}

		// check if a variable is contained in the collection based on its id and category
		public bool contains(string id, string category) {
			if(id == null || category == null) { return false; }

			int categoryIndex = indexOfCategory(category);

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   categoryIndex == m_variables[i].category) {
					return true;
				}
			}
			return false;
		}

		// check if an already existing variable is contained in the collection
		public bool contains(Variable v) {
			if(v == null) { return false; }

			for(int i=0;i<m_variables.Count();i++) {
				if(v.id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   v.category == m_variables[i].category) {
					return true;
				}
			}
			return false;
		}

		// get the index of a variable from the collection based on its id if it exists
		public int indexOf(string id) {
			if(id == null) { return -1; }

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase)) {
					return i;
				}
			}
			return -1;
		}

		// get the index of a variable from the collection based on its id and category if it exists
		public int indexOf(string id, string category) {
			if(id == null || category == null) { return -1; }

			int categoryIndex = indexOfCategory(category);

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   categoryIndex == m_variables[i].category) {
					return i;
				}
			}
			return -1;
		}

		// get the index of an already existing variable from the collection
		public int indexOf(Variable v) {
			if(v == null) { return -1; }

			for(int i=0;i<m_variables.Count();i++) {
				if(v.id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   v.category == m_variables[i].category) {
					return i;
				}
			}
			return -1;
		}

		// get a variable based on a specific index
		public Variable elementAt(int index) {
			if(index < 0 || index >= m_variables.Count()) { return null; }
			return m_variables[index];
		}

		// get a variable based on a specific id
		public Variable getVariable(string id) {
			if(id == null) { return null; }

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase)) {
					return m_variables[i];
				}
			}
			return null;
		}

		// get a variable based on a specific id and category
		public Variable getVariable(string id, string category) {
			if(id == null || category == null) { return null; }

			int categoryIndex = indexOfCategory(category);

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   categoryIndex == m_variables[i].category) {
					return m_variables[i];
				}
			}
			return null;
		}

		// get a variable value on a specific id
		public string getValue(string id) {
			if(id == null) { return null; }

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase)) {
					return m_variables[i].value;
				}
			}
			return null;
		}

		// get a variable value on a specific id and category
		public string getValue(string id, string category) {
			if(id == null || category == null) { return null; }

			int categoryIndex = indexOfCategory(category);

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   categoryIndex == m_variables[i].category) {
					return m_variables[i].value;
				}
			}
			return null;
		}

		// add a new variable from a specified id and value (create the variable)
		public bool add(string id, string value) {
			if(id == null || value == null) { return false; }
			if(!contains(id, "")) {
				m_variables.Add(new Variable(id, value, Variable.NO_CATEGORY));
				return true;
			}
			return false;
		}

		// add a new variable from a specified id, value and category (create the variable)
		public bool add(string id, string value, string category) {
			if(id == null || value == null || category == null) { return false; }
			if(!contains(id, category)) {
				int categoryIndex = addCategory(category);
				m_variables.Add(new Variable(id, value, categoryIndex));
				return true;
			}
			return false;
		}

		// add an already existing variable
		public bool add(Variable v) {
			if(v == null) { return false; }
			if(!contains(v) && v.category < m_categories.Count()) {
				m_variables.Add(v);
				return true;
			}
			return false;
		}

		// update the string value of a variable based on its id
		public void setValue(string id, string value) {
			if(id == null || value == null) { return; }

			bool valueUpdated = false;

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase)) {
					m_variables[i].value = value;
					valueUpdated = true;
				}
			}

			// if the variable doesn't exist, add it
			if(!valueUpdated) {
				add(id, value);
			}
		}

		// update the integer value of a variable based on its id
		public void setValue(string id, int value) {
			setValue(id, value.ToString());
		}

		// update the floating point value of a variable based on its id
		public void setValue(string id, double value) {
			setValue(id, value.ToString());
		}

		// update the boolean value of a variable based on its id
		public void setValue(string id, bool value) {
			setValue(id, value.ToString().ToLower());
		}

		// update the string value of a variable based on its id and category
		public void setValue(string id, string value, string category) {
			if(id == null || category == null) { return; }

			int categoryIndex = indexOfCategory(category);

			bool valueUpdated = false;

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   categoryIndex == m_variables[i].category) {
					m_variables[i].value = value;
					valueUpdated = true;
				}
			}

			// if the variable doesn't exist, add it
			if(!valueUpdated) {
				add(id, value, category);
			}
		}

		// update the integer value of a variable based on its id and category
		public void setValue(string id, int value, string category) {
			setValue(id, value.ToString(), category);
		}

		// update the floating point value of a variable based on its id and category
		public void setValue(string id, double value, string category) {
			setValue(id, value.ToString(), category);
		}

		// update the boolean value of a variable based on its id and category
		public void setValue(string id, bool value, string category) {
			setValue(id, value.ToString().ToLower(), category);
		}

		// remove a specific variable based on its index
		public bool remove(int index) {
			if(index < 0 || index >= m_variables.Count()) { return false; }
			m_variables.RemoveAt(index);
			return true;
		}

		// remove a specific variable based on its id
		public bool remove(string id) {
			if(id == null) { return false; }

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase)) {
					m_variables.RemoveAt(i);
					return true;
				}
			}
			return false;
		}

		// remove a specific variable based on its id and category
		public bool remove(string id, string category) {
			if(id == null || category == null) { return false; }

			int categoryIndex = indexOfCategory(category);

			for(int i=0;i<m_variables.Count();i++) {
				if(id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   categoryIndex == m_variables[i].category) {
					m_variables.RemoveAt(i);
					return true;
				}
			}
			return false;
		}

		// remove an already existing variable
		public bool remove(Variable v) {
			if(v == null) { return false; }

			for(int i=0;i<m_variables.Count();i++) {
				if(v.id.Equals(m_variables[i].id, StringComparison.OrdinalIgnoreCase) &&
				   v.category == m_variables[i].category) {
					m_variables.RemoveAt(i);
					return true;
				}
			}
			return false;
		}

		// clear all variables
		public void clear() {
			m_variables.Clear();
		}

		// group all variables together based on their categories
		public void sort() {
			Variable temp;
			for(int i=0;i<m_variables.Count();i++) {
				for(int j=i;j<m_variables.Count();j++) {
					if(m_variables[i].category > m_variables[j].category) {
						temp = m_variables[i];
						m_variables[i] = m_variables[j];
						m_variables[j] = temp;
					}
				}
			}
		}

		// parse a collection of variables from a file
		public static VariableSystem readFrom(string fileName) {
			if(fileName == null || fileName.Length == 0) { return null; }

			string data;

			// open the file
			StreamReader input = null;
			try {
				input = File.OpenText(fileName);
			}
			catch(Exception e) {
				Console.WriteLine("Error reading variables from file \"" + fileName + "\": " + e.Message);
				return null;
			}

			VariableSystem variables = new VariableSystem();
			string category = null;
			int categoryIndex = -1;

			// read to the end of the file
			while((data = input.ReadLine()) != null) {
				data = data.Trim();
				if(data.Length == 0) {
					category = null;
					categoryIndex = -1;
					continue;
				}

				// parse a category
				if(data[0] == '[' && data[data.Length-1] == ']') {
					category = data.Substring(1, data.Length - 2);
					categoryIndex = variables.addCategory(category);
				}
				// parse a variable
				else {
					Variable v = Variable.parseFrom(data);
					if(v != null) {
						v.category = categoryIndex;
						variables.add(v);
					}
				}
			}

			if(input != null) { input.Close(); }

			return variables;
		}

		public bool writeTo(string fileName) {
			int lastCategory = -1;

			bool firstLine = true;

			// open the file
			StreamWriter output = null;
			try {
				output = File.CreateText(fileName);
			}
			catch(Exception e) {
				Console.WriteLine("Error writing variables to file \"" + fileName + "\": " + e.Message);
				return false;
			}

			// output all of the variables to the file, grouped under corresponding categories
			for(int i=0;i<m_variables.Count();i++) {
				if(lastCategory == -1 || lastCategory != m_variables[i].category) {
					if(m_variables[i].category != -1) {
						if(!firstLine) { output.WriteLine(); }
						output.WriteLine("[" + m_categories[m_variables[i].category] + "]");
						firstLine = false;
					}
					lastCategory = m_variables[i].category;
				}
				m_variables[i].writeTo(output);
				output.WriteLine();
				firstLine = false;
			}

			if(output != null) { output.Close(); }

			return true;
		}

		public override int GetHashCode() {
			return base.GetHashCode();
		}

		public override bool Equals(object o) {
			VariableSystem v = o as VariableSystem;
			if(v == null) { return false; }
			return m_variables.Equals(v.m_variables);
		}

		public override string ToString() {
			string s = "";
			for(int i=0;i<m_variables.Count();i++) {
				s += m_variables[i];
				if(i<m_variables.Count()-1) {
					s += '\n';
				}
			}
			return s;
		}

	}

}
