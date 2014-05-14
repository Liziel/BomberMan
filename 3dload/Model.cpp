#include "Model.hpp"
#include "SFML/OpenGL.hpp"

Model::Model(std::string name)
{
  this->_name = name;
  this->_dist = "./models/" + this->_name;
}

void Model::load()
{
  std::ifstream in;
  std::string buffer;
  std::string type;
  std::string values;
  std::string poss_types[4] = { "v", "vn", "vt", "f" };
  parseModel fcts[] = { &Model::parseV, &Model::parseVn, &Model::parseVt, &Model::parseF };
  int pos;
  int i;

  in.open(this->_dist.c_str());
  while (getline(in, buffer))
    {
      if ((pos = buffer.find(" ")) != buffer.npos)
	{
	  type = buffer.substr(0, pos);
	  values = buffer.substr(pos + 1, buffer.length());
	}
      for (i = 0; i < 4; i++)
	{
	  if (poss_types[i] == type)
	    (this->*fcts[i]) (values);
	}
    }
  in.close();
}

void Model::parseV(std::string values)
{
  struct s_val<float> parsed;
  int	pos;
  int	i;
  double val;
  std::string splitd;

  for (i = 0; i < 3; i++)
    {
      if ((pos = values.find(" ")) != values.npos)
	{
	  splitd = values.substr(0, pos);
	  values = values.substr(pos + 1, values.npos);
	}
      else
	splitd = values.substr(0, values.length());
      pos = splitd.find(",");
      (pos != splitd.npos) ? (splitd.replace(pos, 1, ".")) : (splitd = splitd);
      std::stringstream ss(splitd);
      ss >> val;
      parsed.vals[i] = val;
    }
  this->v.push_back(parsed);
}

void Model::parseVn(std::string values)
{
  struct s_val<float> parsed;
  int	pos;
  int	i;
  double val;
  std::string splitd;

  for (i = 0; i < 3; i++)
    {
      if ((pos = values.find(" ")) != values.npos)
	{
	  splitd = values.substr(0, pos);
	  values = values.substr(pos + 1, values.npos);
	}
      else
	splitd = values.substr(0, values.length());
      pos = splitd.find(",");
      (pos != splitd.npos) ? (splitd.replace(pos, 1, ".")) : (splitd = splitd);
      std::stringstream ss(splitd);
      ss >> val;
      parsed.vals[i] = val;
    }
  this->vn.push_back(parsed);
}

void Model::parseVt(std::string values)
{
  struct s_val<float> parsed;
  int	pos;
  int	i;
  double val;
  std::string splitd;

  for (i = 0; i < 3; i++)
    {
      if ((pos = values.find(" ")) != values.npos)
	{
	  splitd = values.substr(0, pos);
	  values = values.substr(pos + 1, values.npos);
	}
      else
	splitd = values.substr(0, values.length());
      pos = splitd.find(",");
      (pos != splitd.npos) ? (splitd.replace(pos, 1, ".")) : (splitd = splitd);
      std::stringstream ss(splitd);
      ss >> val;
      parsed.vals[i] = val;
    }
  this->vt.push_back(parsed);
}

void Model::parseF(std::string values)
{
  struct s_val<int> parsed;
  int	pos;
  int	i;
  int	val;
  std::string splitd;

  for (i = 0; i < 9; i++)
    {
      if ((pos = values.find_first_not_of("0123456789")) != values.npos)
	{
	  splitd = values.substr(0, pos);
	  values = values.substr(pos + 1, values.npos);
	}
      else
	splitd = values.substr(0, values.length());
      if (splitd != "")
	{
	  std::stringstream ss(splitd);
	  ss >> val;
	  parsed.vals[i] = val;
	}
      else
	parsed.vals[i] = 0;
    }
  this->f.push_back(parsed);
}

void Model::show(float angle) const
{
  int i = 50;

  //Prepare for drawing
  // Clear color and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Apply some transformations for the cube
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0.f, 0.f, -80.f);

  glRotatef(angle * 50, 1.f, 0.f, 0.f);
  glRotatef(angle * 30, 0.f, 1.f, 0.f);
  glRotatef(angle * 90, 0.f, 0.f, 1.f);

  //Draw a model
  for (std::list<struct s_val<int> >::const_iterator it = this->f.begin() ; it != this->f.end(); ++it)
    {
      glBegin(GL_POLYGON); //draw some polygons
      glColor3ub(i, i, i);
      glVertex3d(this->v[it->vals[0] - 1].vals[0], this->v[it->vals[0] - 1].vals[1], this->v[it->vals[0] - 1].vals[2]);
      glVertex3d(this->v[it->vals[3] - 1].vals[0], this->v[it->vals[3] - 1].vals[1], this->v[it->vals[3] - 1].vals[2]);
      glVertex3d(this->v[it->vals[6] - 1].vals[0], this->v[it->vals[6] - 1].vals[1], this->v[it->vals[6] - 1].vals[2]);
      (i == 85) ? (i = 50) : (i += 35);
      glEnd();
    }
}

void Model::serializeVertex()
{
  //
}
