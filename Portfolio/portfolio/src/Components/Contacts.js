import lnkdin from '../Assets/linkedin.png';
import email from '../Assets/email.png';
import git from '../Assets/github.png';

const Contacts = () => {
    return (
      <div id='contacts' className='contacts'>
        <div className="contacts-heading">
          <h2 style={{ fontSize: '70px' }}>Contacts</h2>
        </div>
        <div className="info">
          <h3 style={{ fontSize: '40px', textAlign: 'center', marginTop: '60px' }}>You can find me on:</h3>
          <div className="contact-container">
            <div className="contact-item">
              <a href="https://www.linkedin.com/in/shaun-jac0b/" target="_blank" rel="noopener noreferrer">
                <img src={lnkdin} alt='lin_icon' className='contact-img' />
              </a>
              <p>Linkedin</p>
            </div>
            <div className="contact-item">
              <a href="mailto:ssj9132@mavs.uta.com">
                <img src={email} alt='email_icon' className='contact-img' />
              </a>
              <p>Email: ssj9132@mavs.uta.edu</p>
            </div>
            <div className="contact-item">
              <a href="https://github.com/ssj9132/cse1325" target="_blank" rel="noopener noreferrer">
                <img src={git} alt='git_icon' className='contact-img' />
              </a>
              <p>Github</p>
            </div>
          </div>
        </div>
      </div>
    );
};

export default Contacts;
