import Sigma from '../Assets/sigma_app.png';
import Lms from '../Assets/lms_java.jpg';
import Portfolio from '../Assets/portfolio_img.png';
import Alarm from '../Assets/alarmClient.jpg';

const Projects = () => {
    return (  
        <div id='projects' className="projects">
            <div className="projects-heading">
                <h2 style={{fontSize:'70px'}}>Projects</h2>
            </div>
            <div className='filters'>
                <button className="filter-button">All</button>
                <button className="filter-button">Software</button>
                <button className="filter-button">Hardware</button>
            </div>
            <p><br /></p>
            <div className="projects-images">
                <div className="image-container">
                    <img src={Sigma} alt="Sigma app" className="project-image" />
                    <div className="overlay">
                        <div className="text">Sigma App</div>
                    </div>
                </div>
                <div className="image-container">
                    <img src={Lms} alt="Lms app" className="project-image" />
                    <div className="overlay">
                        <div className="text">LMS App</div>
                    </div>
                </div>
                <div className="image-container">
                    <img src={Portfolio} alt="Portfolio site" className="project-image" />
                    <div className="overlay">
                        <div className="text">Portfolio Site</div>
                    </div>
                </div>
                <div className="image-container">
                    <img src={Alarm} alt="Alarm" className="project-image" />
                    <div className="overlay">
                        <div className="text">Burglar Alarm Client</div>
                    </div>
                </div>
            </div>
        </div>
    );
}
 
export default Projects;
