using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TripeTriadUI
{
    public class RulesModel
    {
        public class Rule : INotifyPropertyChanged
        {
            public string Name { get; set; }
            public bool Value { get; set; }
            public event PropertyChangedEventHandler? PropertyChanged;
            public Rule(string name, bool value)
            {
                Name = name;
                Value = value;
            }
            protected void OnPropertyChanged(string propertyName)
            {
                PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
            }
            public void SetValue(bool value)
            {
                Value = value;
                OnPropertyChanged(nameof(Value));
            }

        }

        public List<Rule> Rules { get; set; }
        public RulesModel() {
            Rules = new List<Rule>
            {
                new Rule("Standard", true),
                new Rule("Open", true),
                new Rule("Same", false),
                new Rule("Plus", false),
                new Rule("Wall", false),
                new Rule("Cascade", false)
            };
        }
        public bool? GetRule(string ruleName)
        {
            var rule = Rules.FirstOrDefault(r => r.Name.Equals(ruleName, StringComparison.OrdinalIgnoreCase));
            return rule?.Value;
        }
        public void SetRule(string ruleName, bool value)
        {
            var rule = Rules.FirstOrDefault(r => r.Name.Equals(ruleName, StringComparison.OrdinalIgnoreCase));
            if (rule != null)
            {
                rule.SetValue(value);
            }
        }
        public override String ToString()
        {
            StringBuilder sb = new StringBuilder();
            foreach (var rule in Rules)
            {
                if (rule.Value)
                {
                    sb.Append(rule.Name);
                }
            }
            return sb.ToString();

        }
    }
}
