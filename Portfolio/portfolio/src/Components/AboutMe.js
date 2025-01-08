import '../index.css';
import Shaun from '../Assets/Shaun.jpg';

const About = () => {
    return (
        <div id='about' className='About'>
            <h2 className='about-me-heading'>About Me</h2>
            <div className='aboutMe'>
                <img className='shaun-img' src={Shaun} alt="Shaun pic" />
                <div className='aboutMe-text'>
                    <p>I am a junior Computer Engineering student at the University of Texas at Arlington, dedicated to being a Jack of All Trades with expertise in both software and hardware. I pride myself on being a versatile problem solver, continuously honing my leadership skills
                         and striving for excellence in all my pursuits.<br /><br />Currently as a Learning Specialist at the Learning Access Center, I empower students with disabilities by tutoring them in various STEM subjects, from General Physics to Discrete Structures, and crafting personalized learning plans alongside resume development..<br /><br />
                        Along with that, I have work experiences in multiple different fields ranging from a Business Development and Innovation Integration Intern at Expo 2020 Dubai to 
                        a Front-End Development Intern at ALEC Dubai, providing me with a diverse perspective on going about with things. 
                        I am highly interested in creating an inclusive experience for everyone by improving accessibility especially through Assistive Technology.
                    </p>
                </div>
            </div>
            <div className='education-container'>
                <div className='education'>
                    <h3>Education</h3>
                    <p style={{fontWeight: 'bold', fontSize: '23px', marginTop: '30px'}}>University of Texas at Arlington</p>
                    <p style={{marginTop: '-15px', fontStyle: 'italic'}}>Arlington, TX</p>
                    <div className='degree-info'>
                        <p><b>Degree:</b> Bachelor of Science in Computer Engineering (Honors)</p>
                        <p><b>GPA:</b> 3.96</p>
                        <p><b>Expected Graduation:</b> May 2026</p>
                    </div>
                </div>
                <div className='coursework'>
                    <h5>Relevant Coursework:</h5>
                    <ul>
                        <li>Operating Systems</li>
                        <li>Digital Logic and Design -1</li>
                        <li>Object Oriented Programming</li>
                        <li>Embedded Systems -1</li>
                        <li>Data Structures and Algorithms</li>
                        <li>Computer Organization and Assembly</li>
                    </ul>
                </div>
            </div>
        </div>
    );
};

export default About;
