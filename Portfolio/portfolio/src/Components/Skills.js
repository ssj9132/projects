import '../index.css';

const Skills = () => {
  return (
    <div id='skills' className="Skills">
      <h2 className="skills-heading">Skills</h2>

      <div className='headings-container'>
        <h4 className='headings'>Languages</h4>
        <div className='Skill-Container'>
          <div className="Skill">
            <img src="https://cdn4.iconfinder.com/data/icons/logos-and-brands/512/181_Java_logo_logos-512.png"
              alt="java"
              style={{ width: '150px', height: 'auto' }} />
            <h5>Java</h5>
          </div>
          <div className="Skill">
            <img src="https://cdn4.iconfinder.com/data/icons/logos-and-brands/512/267_Python_logo-512.png"
              alt="python"
              style={{ width: '150px', height: 'auto' }} />
            <h5>Python</h5>
          </div>
          <div className="Skill">
            <img src="https://cdn4.iconfinder.com/data/icons/logos-brands-in-colors/404/c_logo-256.png"
              alt="C++"
              style={{ width: '150px', height: 'auto' }} />
            <h5>C++</h5>
          </div>
          <div className="Skill">
            <img src="https://upload.wikimedia.org/wikipedia/commons/1/19/C_Logo.png"
              alt="C++"
              style={{ width: '135px', height: '140px' }} />
            <h5>C</h5>
          </div>
          <div className="Skill">
            <img src="https://cdn1.iconfinder.com/data/icons/logotypes/32/badge-html-5-256.png"
              alt="html"
              style={{ width: '135px', height: 'auto' }} />
            <h5>HTML5</h5>
          </div>
          <div className="Skill">
            <img src="https://cdn1.iconfinder.com/data/icons/logotypes/32/badge-css-3-512.png"
              alt="css"
              style={{ width: '135px', height: 'auto' }} />
            <h5>CSS3</h5>
          </div>
          <div className="Skill">
            <img src="https://cdn1.iconfinder.com/data/icons/ionicons-fill-vol-2/512/logo-javascript-256.png"
              alt="js"
              style={{ width: '135px', height: 'auto' }} />
            <h5>JavaScript</h5>
          </div>
          <div className="Skill">
            <img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTDE1fj9T4URvQ0S_pbzIiVZPIncehycM70zw&s"
              alt="arm"
              style={{ width: '135px', height: 'auto' }} />
            <h5>ARM</h5>
          </div>
          <div className="Skill">
            <img src="https://icons.veryicon.com/png/o/business/vscode-program-item-icon/verilog.png"
              alt="verilog"
              style={{ width: '135px', height: 'auto' }} />
            <h5>Verilog</h5>
          </div>
        </div>
      </div>

      <div className='headings-container'>
        <h4 className='headings'>Libraries</h4>
        <div className='Skill-Container'>
          <div className="Skill">
            <img src="https://cdn0.iconfinder.com/data/icons/logos-brands-in-colors/128/react_color-256.png"
              alt="react"
              style={{ width: '150px', height: 'auto' }} />
            <h5>React</h5>
          </div>
          <div className="Skill">
            <img src="https://static-00.iconduck.com/assets.00/file-type-numpy-icon-476x512-106d391z.png"
              alt="numpy"
              style={{ width: '150px', height: 'auto' }} />
            <h5>NumPy</h5>
          </div>
          <div className="Skill">
            <img src="https://www.linuxfoundation.org/hs-fs/hubfs/PyTorchLogo_Icon_fullColor_RGB.png?width=259&height=288&name=PyTorchLogo_Icon_fullColor_RGB.png"
              alt="pytorch"
              style={{ width: '150px', height: 'auto' }} />
            <h5>PyTorch</h5>
          </div>
          <div className="Skill">
            <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/9/97/Sqlite-square-icon.svg/1200px-Sqlite-square-icon.svg.png"
              alt="sqlite"
              style={{ width: '150px', height: 'auto' }} />
            <h5>SQLite</h5>
          </div>
        </div>
      </div>

      <div className='sections-container'>
        <div className='headings-container'>
          <h4 className='headings'>Databases</h4>
          <div className='Skill-Container'>
            <div className="Skill">
              <img src="https://cdn4.iconfinder.com/data/icons/logos-3/181/MySQL-256.png"
                alt="mysql"
                style={{ width: '150px', height: 'auto' }} />
              <h5>MySQL</h5>
            </div>
            <div className="Skill">
              <img src="https://cdn4.iconfinder.com/data/icons/logos-3/512/mongodb-2-256.png"
                alt="mongo"
                style={{ width: '150px', height: 'auto' }} />
              <h5>MongoDB</h5>
            </div>
          </div>
        </div>

        <div className='headings-container'>
          <h4 className='headings'>Developer Tools</h4>
          <div className='Skill-Container'>
            <div className="Skill">
              <img src="https://cdn3.iconfinder.com/data/icons/social-media-2169/24/social_media_social_media_logo_git-512.png"
                alt="git"
                style={{ width: '150px', height: 'auto' }} />
              <h5>Git</h5>
            </div>
            <div className="Skill">
              <img src="https://dwglogo.com/wp-content/uploads/2019/03/1800px-gnu_bash_logo.png"
                alt="bash"
                style={{ width: '200px', height: 'auto' }} />
              <h5>Bash</h5>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Skills;
